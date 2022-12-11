#include "ReactSkia/ComponentViewRegistry.h"

#include <glog/logging.h>

namespace facebook {
namespace react {

ComponentViewRegistry::ComponentViewRegistry() {
  descriptorProviderRegistry_ =
      std::make_unique<ComponentDescriptorProviderRegistry>();
}

ComponentDescriptorRegistry::Shared
ComponentViewRegistry::CreateComponentDescriptorRegistry(
    ComponentDescriptorParameters const &parameters) {
  componentDescriptorRegistry_ = descriptorProviderRegistry_->createComponentDescriptorRegistry(
      parameters);
  return componentDescriptorRegistry_;
}

void ComponentViewRegistry::Register(
    std::unique_ptr<RSkComponentProvider> provider) {
  auto descriptorProvider = provider->GetDescriptorProvider();
  descriptorProviderRegistry_->add(descriptorProvider);
  registry_[descriptorProvider.handle] = std::move(provider);
}

void ComponentViewRegistry::Register(
    std::unique_ptr<RSkComponentProvider> provider,
    ComponentHandle handle) {
  registry_[handle] = std::move(provider); //Dont have to add descriptorProvider to descriptorProviderRegistry_. Use other overloaded Register function for that
}

RSkComponentProvider *ComponentViewRegistry::GetProvider(
    ComponentName componentName) {
  for (const auto &kv : registry_) {
    if (strcmp(kv.second->GetDescriptorProvider().name, componentName) == 0) {
      return kv.second.get();
    }
  }
  return nullptr;
}

RSkComponentProvider *ComponentViewRegistry::GetProvider(
    ComponentHandle componentHandle) {
  auto it = registry_.find(componentHandle);
  if (it != registry_.end()) {
    return it->second.get();
  }
  return nullptr;
}

RSkComponent* ComponentViewRegistry::GetComponent(
    int tag, const ComponentDescriptor** componentDescriptor) const {

  for(const auto &kv : registry_) {
    if (strcmp(kv.second->GetDescriptorProvider().name, "RootView")) {
      if(kv.second->GetComponent(tag) != nullptr) {
        *componentDescriptor = componentDescriptorRegistry_->findComponentDescriptorByHandle_DO_NOT_USE_THIS_IS_BROKEN(kv.second->GetDescriptorProvider().handle);
        return kv.second->GetComponent(tag).get();
      }
    }
  }
  return nullptr;
}

} // namespace react
} // namespace facebook
