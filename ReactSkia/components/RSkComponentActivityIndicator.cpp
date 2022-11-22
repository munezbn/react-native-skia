#include <ReactSkia/activityindicator/react/renderer/components/activityindicator/ActivityIndicatorProps.h>
#include "ReactSkia/components/RSkComponentActivityIndicator.h"

#include "ReactSkia/utils/RnsLog.h"

namespace facebook {
namespace react {

RSkComponentActivityIndicator::RSkComponentActivityIndicator(const ShadowView &shadowView)
    : RSkComponent(shadowView) {}

RSkComponentActivityIndicator::~RSkComponentActivityIndicator(){}

RnsShell::LayerInvalidateMask  RSkComponentActivityIndicator::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {return RnsShell::LayerInvalidateNone;}
void RSkComponentActivityIndicator::OnPaint(SkCanvas *canvas) {
  auto component = getComponentData();
  auto const &activityIndicatorProps = *std::static_pointer_cast<ActivityIndicatorProps const>(component.props);

  auto borderMetrics=activityIndicatorProps.resolveBorderMetrics(component.layoutMetrics);
  Rect frame = component.layoutMetrics.frame;

  /*Yet to implement the activity indicator drawings...*/
}

} // namespace react
} // namespace facebook
