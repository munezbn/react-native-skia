#pragma once

#include "ReactSkia/components/RSkComponentProvider.h"

namespace facebook {
namespace react {

class RSkComponentProviderActivityIndicator final: public RSkComponentProvider {
 public:
  RSkComponentProviderActivityIndicator();

 public:
  ComponentDescriptorProvider GetDescriptorProvider() override;
  std::shared_ptr<RSkComponent> CreateComponent(
      const ShadowView &shadowView) override;
};

} // namespace react
} // namespace facebook
