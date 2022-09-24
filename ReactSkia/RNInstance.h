#pragma once

#include "cxxreact/Instance.h"
#include "react/renderer/scheduler/SurfaceHandler.h"

#include "rns_shell/platform/linux/TaskLoop.h"

namespace RnsShell {
  class RendererDelegate;
}

namespace facebook {
namespace react {

using namespace RnsShell;

class ComponentViewRegistry;
class JSITurboModuleManager;
class MountingManager;
class Scheduler;
class RSkSurfaceWindow;

class RNInstance {
 public:
  RNInstance(RendererDelegate &rendererDelegate);
  ~RNInstance();
  RNInstance(RNInstance &&) = default;

  void Start(RSkSurfaceWindow *surface, RendererDelegate &rendererDelegate);
  void Stop(RSkSurfaceWindow *surface);

 private:
  void InitializeJSCore();
  void InitializeFabric(RendererDelegate &rendererDelegate);
  void RegisterComponents();

 private:
  std::unique_ptr<Instance> instance_;
  std::unique_ptr<JSITurboModuleManager> turboModuleManager_;
  std::shared_ptr<Scheduler> fabricScheduler_;
  std::unique_ptr<MountingManager> mountingManager_;
  std::unique_ptr<ComponentViewRegistry> componentViewRegistry_;
  std::map<SurfaceId,SurfaceHandler> surfaceHandlerList_;
  std::unique_ptr<RnsShell::TaskLoop> backgroundTaskRunner_{nullptr};
  std::thread backgroundThread_;
};

} // namespace react
} // namespace facebook
