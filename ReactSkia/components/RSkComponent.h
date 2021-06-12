#pragma once

#include "include/core/SkCanvas.h"
#include "react/renderer/mounting/ShadowView.h"
#include "sk_app/Window.h"
#include <glog/logging.h>

//#include "ReactSkia/core_modules/RSkSpatialNavigator.h"
namespace SpatialNavigator {
  class RSkSpatialNavigator;
}

namespace facebook {
namespace react {

enum ComponentUpdateMask {
  ComponentUpdateMaskNone = 0,
  ComponentUpdateMaskProps = 1 << 0,
  ComponentUpdateMaskEventEmitter = 1 << 1,
  ComponentUpdateMaskState = 1 << 2,
  ComponentUpdateMaskLayoutMetrics = 1 << 3,

  ComponentUpdateMaskAll = ComponentUpdateMaskProps | ComponentUpdateMaskEventEmitter |
      ComponentUpdateMaskState | ComponentUpdateMaskLayoutMetrics
};

struct Component {
  Component( const ShadowView &shadowView)
    : props(shadowView.props)
    , eventEmitter(shadowView.eventEmitter)
    , layoutMetrics(shadowView.layoutMetrics)
    , state(shadowView.state)
    , tag (shadowView.tag)
  {}

  Props::Shared props{};
  EventEmitter::Shared eventEmitter{};
  LayoutMetrics layoutMetrics{EmptyLayoutMetrics};
  State::Shared state{};
  Tag tag{};
  // TO DO: Setup the data types correctly
  int bottomY;
  int rightX;
  bool onBlur() { return false; }
  bool onFocus() { return false; }

};

class RSkComponent : public sk_app::Window::Layer {
 public:
  RSkComponent(const ShadowView &shadowView);
  RSkComponent(RSkComponent &&) = default;
  RSkComponent &operator=(RSkComponent &&) = default;

  virtual ~RSkComponent();

  virtual void mountChildComponent(
    std::shared_ptr<RSkComponent> newChildComponent,
    const int index);

  virtual void unmountChildComponent(
    std::shared_ptr<RSkComponent> oldChildComponent,
    const int index);

  virtual void updateComponentData(const ShadowView &newShadowView , const uint32_t updateMask);
  Component getComponentData() { return component_;};
  Point getFrameOrigin() { return absOrigin_;};
  Size getFrameSize() { return component_.layoutMetrics.frame.size;};

 protected:
  virtual void OnPaint(SkCanvas *canvas) = 0;

 private:
  // sk_app::Window::Layer implementations
  void onPaint(SkSurface *surface) override;

 private:
  RSkComponent *parent_;
  Point absOrigin_;
  Component component_;

  SpatialNavigator::RSkSpatialNavigator *spatialNavigator_; 
};

} // namespace react
} // namespace facebook
