#pragma once

#include "include/core/SkRect.h"

#include "react/renderer/components/image/ImageShadowNode.h"

#include "ReactSkia/components/RSkComponent.h"
#include "ReactSkia/views/common/RSkImageCacheManager.h"

#define DEFAULT_IMAGE_FILTER_QUALITY kLow_SkFilterQuality /*Skia's Defualt is kNone_SkFilterQuality*/

namespace facebook {
namespace react {

struct ImgProps{
    ImageResizeMode resizeMode;
    SkColor tintColor;
};

class RSkComponentImage final : public RSkComponent {
 public:
  RSkComponentImage(const ShadowView &shadowView);
  RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;

 private :
  ImgProps imageProps;

  sk_sp<SkImage> getLocalImageData(ImageSource source);
  void requestNetworkImageData(ImageSource source);

  inline string generateUriPath(string path);
  void drawAndSubmit();
  void processImageData(const char* path, char* response, int size);

 protected:
  void OnPaint(SkCanvas *canvas) override;
};

} // namespace react
} // namespace facebook
