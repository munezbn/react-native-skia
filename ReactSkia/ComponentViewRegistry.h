#pragma once

#include "ReactSkia/components/RSkComponentProvider.h"

#include "better/map.h"
#include "react/renderer/componentregistry/ComponentDescriptorRegistry.h"
#include "react/renderer/componentregistry/ComponentDescriptorProviderRegistry.h"
#include "react/renderer/core/ReactPrimitives.h"

namespace facebook {
namespace react {

class ComponentViewRegistry {
 public:
  ComponentViewRegistry();
  ComponentViewRegistry(ComponentViewRegistry &&) = default;
  ComponentViewRegistry &operator=(ComponentViewRegistry &&) = default;

  void Register(std::unique_ptr<RSkComponentProvider> provider);
  void Register(std::unique_ptr<RSkComponentProvider> provider, ComponentHandle handle);

  ComponentDescriptorRegistry::Shared CreateComponentDescriptorRegistry(
      ComponentDescriptorParameters const &parameters) ;

  RSkComponentProvider *GetProvider(ComponentName componentName);
  RSkComponentProvider *GetProvider(ComponentHandle componentHandle);
  RSkComponent* GetComponent(int tag, const ComponentDescriptor** componentDescriptor) const;

  ComponentDescriptorProviderRegistry& providerRegistry() { return *descriptorProviderRegistry_; }

 private:
  std::unique_ptr<ComponentDescriptorProviderRegistry>
      descriptorProviderRegistry_;
  ComponentDescriptorRegistry::Shared componentDescriptorRegistry_;
  better::map<ComponentHandle, std::unique_ptr<RSkComponentProvider>> registry_;
};

} // namespace react
} // namespace facebook
