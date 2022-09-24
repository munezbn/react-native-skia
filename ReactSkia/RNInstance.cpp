#include <folly/io/async/ScopedEventBaseThread.h>

#include "ReactSkia/RNInstance.h"

#include "ReactSkia/ComponentViewRegistry.h"
#include "ReactSkia/JSITurboModuleManager.h"
#include "ReactSkia/LegacyNativeModules/LegacyNativeModuleRegistry.h"
#include "ReactSkia/MountingManager.h"
#include "ReactSkia/RSkSurfaceWindow.h"
#include "ReactSkia/components/RSkComponentProviderImage.h"
#include "ReactSkia/components/RSkComponentProviderRootView.h"
#include "ReactSkia/components/RSkComponentProviderScrollView.h"
#include "ReactSkia/components/RSkComponentProviderText.h"
#include "ReactSkia/components/RSkComponentProviderTextInput.h"
#include "ReactSkia/components/RSkComponentProviderUnimplementedView.h"
#include "ReactSkia/components/RSkComponentProviderView.h"

#if defined (OS_MACOSX)
#include "ReactSkia/platform/macosx/MainRunLoopEventBeat.h"
#include "ReactSkia/platform/macosx/RuntimeEventBeat.h"
#elif defined (OS_LINUX)
#include "ReactSkia/platform/linux/MainRunLoopEventBeat.h"
#include "ReactSkia/platform/linux/RuntimeEventBeat.h"
#endif
#include "ReactSkia/utils/RnsLog.h"
#include "ReactSkia/utils/AppLog.h"
#include "ReactSkia/views/common/RSkConversion.h"

#include "ReactCommon/TurboModuleBinding.h"
#include "cxxreact/JSBigString.h"
#include "cxxreact/MessageQueueThread.h"
#include "cxxreact/ModuleRegistry.h"
#include "jsi/JSCRuntime.h"
#include "jsireact/JSIExecutor.h"
#include "react/config/ReactNativeConfig.h"
#include "react/renderer/componentregistry/ComponentDescriptorProviderRegistry.h"
#include "react/renderer/components/root/RootShadowNode.h"
#include "react/renderer/scheduler/Scheduler.h"
#include "react/renderer/scheduler/SchedulerToolbox.h"
#include <react/renderer/scheduler/AsynchronousEventBeat.h>
#include "react/utils/ContextContainer.h"

#include "rns_shell/compositor/RendererDelegate.h"

namespace facebook {
namespace react {

class JSCExecutorFactory : public JSExecutorFactory {
 public:
  JSCExecutorFactory(JSITurboModuleManager *jsiTurboModuleManager)
      : jsiTurboModuleManager_(jsiTurboModuleManager) {}

  std::unique_ptr<JSExecutor> createJSExecutor(
      std::shared_ptr<ExecutorDelegate> delegate,
      std::shared_ptr<MessageQueueThread> jsQueue) override {
    auto installBindings = [jsiTurboModuleManager =
                                jsiTurboModuleManager_](jsi::Runtime &runtime) {
    react::bindNativeLogger(runtime, rnsLoggingBinder);

    PerformanceNow rnsPerformanceNowBinder = [](){
       return SkTime::GetMSecs();
    };
    react::bindNativePerformanceNow(runtime, rnsPerformanceNowBinder);

    TurboModuleBinding::install(
          runtime, std::move(jsiTurboModuleManager->GetProvider()));
    };
    return std::make_unique<JSIExecutor>(
        facebook::jsc::makeJSCRuntime(),
        delegate,
        JSIExecutor::defaultTimeoutInvoker,
        std::move(installBindings));
  }

 private:
  JSITurboModuleManager *jsiTurboModuleManager_;
};

class MessageQueueThreadImpl : public MessageQueueThread {
 public:
  MessageQueueThreadImpl() : thread_("JSThread") {}

  void runOnQueue(std::function<void()> &&task) override {
    thread_.getEventBase()->runInEventBaseThread(std::move(task));
  }
  void runOnQueueSync(std::function<void()> &&task) override {
    thread_.getEventBase()->runInEventBaseThreadAndWait(std::move(task));
  }
  void quitSynchronous() override {}

 private:
  folly::ScopedEventBaseThread thread_;
};

static inline LayoutConstraints RSkGetLayoutConstraintsForSize(SkSize minimumSize, SkSize maximumSize) {
  return {
      .minimumSize = RCTSizeFromSkSize(minimumSize),
      .maximumSize = RCTSizeFromSkSize(maximumSize),
      .layoutDirection = facebook::react::LayoutDirection::LeftToRight, // TODO Hardcode for now and later based on some condition like IOS ??
  };
}

static inline LayoutContext RSkGetLayoutContext(SkPoint viewportOffset) {
  return {.pointScaleFactor = 1.0,
          .swapLeftAndRightInRTL = false,
          .fontSizeMultiplier = 1.0,
          .viewportOffset = RCTPointFromSkPoint(viewportOffset)};
}

RNInstance::RNInstance(RendererDelegate &rendererDelegate) {
  InitializeJSCore();
  RegisterComponents();
  InitializeFabric(rendererDelegate);
}

RNInstance::~RNInstance() {}

void RNInstance::Start(RSkSurfaceWindow *surface, RendererDelegate &rendererDelegate) {
  mountingManager_->BindSurface(surface);

  LayoutContext layoutContext = RSkGetLayoutContext(surface->viewportOffset);
  LayoutConstraints layoutConstraints = RSkGetLayoutConstraintsForSize(surface->minimumSize, surface->maximumSize);

  SurfaceHandler surfaceHandler = SurfaceHandler{surface->moduleName, surface->surfaceId};
  surfaceHandler.setContextContainer(fabricScheduler_->getContextContainer());
  surfaceHandler.setProps(surface->properties);
  surfaceHandler.constraintLayout(layoutConstraints, layoutContext);
  fabricScheduler_->registerSurface(surfaceHandler);
  surfaceHandler.start();
  surfaceHandlerList_.emplace(surface->surfaceId , std::move(surfaceHandler));

#if 0
  fabricScheduler_->startSurface(
      surface->surfaceId,
      surface->moduleName,
      surface->properties,
      layoutConstraints,
      layoutContext,
      {} // mountingOverrideDelegate
  );
#endif
  fabricScheduler_->renderTemplateToSurface(surface->surfaceId, {});

  // NOTE(kudo): Does adding RootView here make sense !?
  auto *provider = componentViewRegistry_->GetProvider(RootComponentName);
  auto component = provider->CreateComponent({});
  component->requiresLayer({}, rendererDelegate);
  RNS_LOG_ASSERT(component->layer(), "Layer Cannot Be Null");
  rendererDelegate.setRootLayer(component->layer());
  surface->navigator()->setRootContainer(component.get());
}

void RNInstance::Stop(RSkSurfaceWindow *surface) {
#if 0
  fabricScheduler_->stopSurface(surface->surfaceId);
#else
  auto it = surfaceHandlerList_.find(surface->surfaceId);
  if(it != surfaceHandlerList_.end()) {
     auto surfaceHandler = std::move(it->second);
     surfaceHandlerList_.erase(it);
     surfaceHandler.stop();
     fabricScheduler_->unregisterSurface(surfaceHandler);
  }
#endif

}

void RNInstance::InitializeJSCore() {
  instance_ = std::make_unique<Instance>();
  turboModuleManager_ =
      std::make_unique<JSITurboModuleManager>(instance_.get());
  auto cb = std::make_unique<InstanceCallback>();
  auto factory =
      std::make_shared<JSCExecutorFactory>(turboModuleManager_.get());
  instance_->initializeBridge(
      std::make_unique<InstanceCallback>(),
      std::make_shared<JSCExecutorFactory>(turboModuleManager_.get()),
      std::make_shared<MessageQueueThreadImpl>(),
      std::make_shared<LegacyNativeModuleRegistry>(componentViewRegistry_.get()));

  // NOTE(kudo): Workaround for TurboModules being fully initialized
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  try {
    auto source = JSBigFileString::fromPath("SimpleViewApp.bundle");
    instance_->loadScriptFromString(
        std::move(source), "SimpleViewApp.bundle", true);
  } catch (const jsi::JSError &ex) {
    std::string exc = ex.what();
    RNS_LOG_ERROR("JS ERROR : " << exc);
  } catch (const std::system_error& ex) {
    std::string exc = ex.what();
    RNS_LOG_ERROR("SYSTEM ERROR : " << exc);
  }
}


void RNInstance::InitializeFabric(RendererDelegate &rendererDelegate) {
  facebook::react::ContextContainer::Shared contextContainer =
      std::make_shared<facebook::react::ContextContainer const>();
  std::shared_ptr<const facebook::react::ReactNativeConfig> reactNativeConfig =
      std::make_shared<facebook::react::EmptyReactNativeConfig const>();

  contextContainer->insert("ReactNativeConfig", reactNativeConfig);
  auto runtimeExecutor = instance_->getRuntimeExecutor();

  auto weakRuntimeScheduler = contextContainer->find<std::weak_ptr<RuntimeScheduler>>("RuntimeScheduler");
  auto runtimeScheduler = weakRuntimeScheduler.hasValue() ? weakRuntimeScheduler.value().lock() : nullptr;
  if (runtimeScheduler) {
    runtimeExecutor = [runtimeScheduler](std::function<void(jsi::Runtime & runtime)> &&callback) {
      runtimeScheduler->scheduleWork(std::move(callback));
    };
  }


  auto toolbox = SchedulerToolbox{};
  toolbox.contextContainer = contextContainer;
  toolbox.componentRegistryFactory =
      [this](
          EventDispatcher::Weak const &eventDispatcher,
          ContextContainer::Shared const &contextContainer)
      -> SharedComponentDescriptorRegistry {
    return componentViewRegistry_->CreateComponentDescriptorRegistry(
        ComponentDescriptorParameters{eventDispatcher, contextContainer, nullptr});
  };
  toolbox.runtimeExecutor = runtimeExecutor;
  // toolbox.mainRunLoopObserverFactory = [](RunLoopObserver::Activity
  // activities,
  //                                         RunLoopObserver::WeakOwner const
  //                                         &owner) {
  //   return std::make_unique<MainRunLoopObserver>(activities, owner);
  // };
  //
  //

  RNS_LOG_INFO("Create bgExe");
  backgroundTaskRunner_ = std::make_unique<RnsShell::TaskLoop>();
  backgroundThread_ =  std::thread([this](){backgroundTaskRunner_->run();});
  RNS_LOG_INFO("Create bgExe");
  backgroundTaskRunner_->waitUntilRunning();

  RNS_LOG_INFO("Create bgExe");
  toolbox.backgroundExecutor = [&](std::function<void()> &&callback) {
      RNS_LOG_INFO("backgroundExecutor execution");
      auto copyableCallback = callback;
#if 1
      backgroundTaskRunner_->dispatch([copyableCallback](){
           copyableCallback();
      });
#else
      TaskLoop::main().dispatch([&,copyableCallback]() {
             copyableCallback();
      });

#endif
  };

  RNS_LOG_INFO("Create bgExe");

  toolbox.synchronousEventBeatFactory =
      [runtimeExecutor](EventBeat::SharedOwnerBox const &ownerBox) {
        return std::make_unique<MainRunLoopEventBeat>(
            ownerBox, runtimeExecutor);
      };

  toolbox.asynchronousEventBeatFactory =
      [runtimeExecutor](EventBeat::SharedOwnerBox const &ownerBox) {
    auto runLoopObserver =
        std::make_unique<RuntimeEventBeat const>(ownerBox->owner);
      return std::make_unique<AsynchronousEventBeat>(std::move(runLoopObserver), runtimeExecutor);
  };
  mountingManager_ =
      std::make_unique<MountingManager>(componentViewRegistry_.get(), rendererDelegate);
  fabricScheduler_ =
      std::make_shared<Scheduler>(toolbox, nullptr, mountingManager_.get());
}

static RSkComponentProviderProtocol RSKThirdPartyFabricComponentsProvider(ComponentName componentName) {
  // This function and has table must be generated by codegen with all the linked thirdparty RSkComponentProviderProtocol
  static std::unordered_map<std::string, RSkComponentProviderProtocol> fabricComponentsClassMap = {
  };

  auto p = fabricComponentsClassMap.find(componentName);
  if (p != fabricComponentsClassMap.end()) {
    auto classFunc = p->second;
    return classFunc;
  }

  return nullptr;
}

static RSkComponentProviderProtocol RSKComponentViewClassWithName(ComponentName componentName) {
  return RSKThirdPartyFabricComponentsProvider(componentName);
}

void RNInstance::RegisterComponents() {
  componentViewRegistry_ = std::make_unique<ComponentViewRegistry>();
  componentViewRegistry_->Register(
      std::make_unique<RSkComponentProviderRootView>());
  componentViewRegistry_->Register(
      std::make_unique<RSkComponentProviderView>());
  componentViewRegistry_->Register(
      std::make_unique<RSkComponentProviderImage>());
  componentViewRegistry_->Register(
      std::make_unique<RSkComponentProviderText>());
  componentViewRegistry_->Register(
      std::make_unique<RSkComponentProviderRawText>());
  componentViewRegistry_->Register(
      std::make_unique<RSkComponentProviderParagraph>());
  componentViewRegistry_->Register(
      std::make_unique<RSkComponentProviderTextInput>());
#if 0
  componentViewRegistry_->Register(
      std::make_unique<RSkComponentProviderScrollView>());
#endif
  // Provider request callback which is called when it doesnt find a viewManagerProvider in componentViewRegistry
  componentViewRegistry_->providerRegistry().setComponentDescriptorProviderRequest(
    [this](ComponentName requestedComponentName) {
      RNS_LOG_WARN("!!!!!!!!!! Requested View Component " << requestedComponentName << ", try to find in thirdparty, else use unimplemented view");

      // Fallback 1 : Try to find thirdparty registry.
      auto providerProtocol = RSKComponentViewClassWithName(requestedComponentName);
      if(providerProtocol) {
        std::unique_ptr<RSkComponentProvider> provider(providerProtocol());
        componentViewRegistry_->Register(std::move(provider));
        return;
      }

      // Fallback 2 : Create UnimplementedView object with given requested name as flavour& handle. Refer RCTComponentViewFactory.mm
      auto flavor = std::make_shared<std::string const>(requestedComponentName);
      auto componentName = ComponentName(flavor->c_str());
      auto componentHandle = reinterpret_cast<ComponentHandle>(componentName);
      auto provider = std::make_unique<RSkComponentProviderUnimplementedView>();
      auto constructor = provider->GetDescriptorProvider().constructor;
      componentViewRegistry_->providerRegistry().add(ComponentDescriptorProvider{componentHandle, componentName, flavor, constructor});
      componentViewRegistry_->Register(std::move(provider), componentHandle); // register localy with given handle.
    });
}

} // namespace react
} // namespace facebook
