#include "ReactSkia/activityindicator/react/renderer/components/activityindicator/ActivityIndicatorComponentDescriptor.h"
#include "ReactSkia/components/RSkComponentActivityIndicator.h"
#include "ReactSkia/components/RSkComponentProviderActivityIndicator.h"

namespace facebook {
namespace react {

RSkComponentProviderActivityIndicator::RSkComponentProviderActivityIndicator() {}

ComponentDescriptorProvider RSkComponentProviderActivityIndicator::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<ActivityIndicatorComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderActivityIndicator::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentActivityIndicator>(shadowView));
}

} // namespace react
} // namespace facebook
