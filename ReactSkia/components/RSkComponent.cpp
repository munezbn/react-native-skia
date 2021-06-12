#include "ReactSkia/components/RSkComponent.h"
#include "ReactSkia/core_modules/RSkSpatialNavigator.h"

#include "include/core/SkPaint.h"
#include "include/core/SkSurface.h"

namespace facebook {
namespace react {

RSkComponent::RSkComponent(const ShadowView &shadowView)
    : parent_(nullptr)
    , absOrigin_(shadowView.layoutMetrics.frame.origin)
    , component_(shadowView)
    {
        spatialNavigator_ = SpatialNavigator::RSkSpatialNavigator::getInstance();
    }

RSkComponent::~RSkComponent() {}

void RSkComponent::onPaint(SkSurface *surface) {
  auto canvas = surface->getCanvas();
  OnPaint(canvas);
}

void RSkComponent::updateComponentData(const ShadowView &newShadowView , const uint32_t updateMask) {
   if(updateMask & ComponentUpdateMaskProps)
      component_.props = newShadowView.props;
   if(updateMask & ComponentUpdateMaskState)
      component_.state = newShadowView.state;
   if(updateMask & ComponentUpdateMaskEventEmitter)
      component_.eventEmitter = newShadowView.eventEmitter;
   if(updateMask & ComponentUpdateMaskLayoutMetrics)
      component_.layoutMetrics = newShadowView.layoutMetrics;

    spatialNavigator_->updateInNavList(*this);
}

void RSkComponent::mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index) {

    if(newChildComponent) {
        newChildComponent->parent_ = this;
        newChildComponent->absOrigin_ =  absOrigin_ + newChildComponent->component_.layoutMetrics.frame.origin;
        spatialNavigator_->addToNavList(*newChildComponent);
    }
    /* TODO : Add the new child to children list */
}

void RSkComponent::unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index) {

    if(oldChildComponent) {
        oldChildComponent->parent_ = nullptr ;
        oldChildComponent->absOrigin_ = oldChildComponent->component_.layoutMetrics.frame.origin;
        spatialNavigator_->removeFromNavList(*oldChildComponent);
    }
    /* TODO : Remove the old child from children list */
}

} // namespace react
} // namespace facebook
