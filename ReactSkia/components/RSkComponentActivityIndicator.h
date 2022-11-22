#pragma once

#include <ReactSkia/components/RSkComponent.h>

namespace facebook {
namespace react {

class RSkComponentActivityIndicator final : public RSkComponent {
 public:
  RSkComponentActivityIndicator(const ShadowView &shadowView);
  ~RSkComponentActivityIndicator();
  RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;
 protected:
  void OnPaint(SkCanvas *canvas) override;
};

} // namespace react
} // namespace facebook
