#include <glog/logging.h>

#include "include/core/SkPaint.h"

#include "react/renderer/components/view/ViewShadowNode.h"

#include "ReactSkia/components/RSkComponentImage.h"
#include "ReactSkia/components/RSkComponentView.h"

namespace facebook {
namespace react {


RSkComponentView::RSkComponentView(const ShadowView &shadowView)
    : RSkComponent(shadowView) {}
RnsShell::LayerInvalidateMask  RSkComponentView::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {return RnsShell::LayerInvalidateNone;}
void RSkComponentView::OnPaint(SkCanvas *canvas) {
  auto component = getComponentData();
  auto const &viewProps = *std::static_pointer_cast<ViewProps const>(component.props);
  /* apply view style props */
  auto borderMetrics=viewProps.resolveBorderMetrics(component.layoutMetrics);
  Rect frame = component.layoutMetrics.frame;

/*Draw Order : 1. Shadow 2. BackGround 3 Border*/
    if(hasVisibleShadow) {
        drawShadow(canvas,frame,borderMetrics,
                    viewProps.backgroundColor,
                    component.shadowProps,
                    layer()->shadowImageFilter,layer()->shadowMaskFilter,
                    layer()->opacity);
    }
    drawBackground(canvas,frame,borderMetrics,viewProps.backgroundColor);
    drawBorder(canvas,frame,borderMetrics,viewProps.backgroundColor);
}

} // namespace react
} // namespace facebook
