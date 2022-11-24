/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"

#include <ReactSkia/activityindicator/react/renderer/components/activityindicator/ActivityIndicatorProps.h>
#include "ReactSkia/components/RSkComponentActivityIndicator.h"
#include "ReactSkia/views/common/RSkConversion.h"

#include "ReactSkia/utils/RnsLog.h"

#define ACTIVITY_INDICATOR_STROKE_WIDTH_RATIO             12.5
#define ACTIVITY_INDICATOR_BG_STROKE_TRANSPARENCY_RATIO   20

namespace facebook {
namespace react {

RSkComponentActivityIndicator::RSkComponentActivityIndicator(const ShadowView &shadowView)
    : RSkComponent(shadowView) {}

RSkComponentActivityIndicator::~RSkComponentActivityIndicator(){}

RnsShell::LayerInvalidateMask  RSkComponentActivityIndicator::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {
  return RnsShell::LayerInvalidateNone;
}

void RSkComponentActivityIndicator::OnPaint(SkCanvas *canvas) {
  auto component = getComponentData();
  auto const &activityIndicatorProps = *std::static_pointer_cast<ActivityIndicatorProps const>(component.props);
  auto borderMetrics=activityIndicatorProps.resolveBorderMetrics(component.layoutMetrics);
  Rect frame = component.layoutMetrics.frame;
  SkPaint paint;
  SkScalar strokeWidth;

  paint.setAntiAlias(true);
  paint.setStyle(SkPaint::kStroke_Style);

  strokeWidth = (frame.size.width * ACTIVITY_INDICATOR_STROKE_WIDTH_RATIO) / 100;
  if(!strokeWidth){
    return;
  }
  paint.setStrokeWidth(strokeWidth);

  if (activityIndicatorProps.color ){
      SkColor strokeColor = RSkColorFromSharedColor(activityIndicatorProps.color, SK_ColorTRANSPARENT);
      SkColor alphaVal = SkColorGetA(strokeColor);

      if (strokeColor && alphaVal){
          SkColor bgStrokeAlphaValue;
          SkPath bgStrokePath;
          SkPath fgStrokePath;
          SkRect rect = SkRect::MakeXYWH(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
          
          rect.inset(strokeWidth/2, strokeWidth/2);
          bgStrokeAlphaValue = (alphaVal * ACTIVITY_INDICATOR_BG_STROKE_TRANSPARENCY_RATIO) / 100;
          
          if(bgStrokeAlphaValue){
              bgStrokePath.addArc(rect, 0, 360);
              paint.setColor(strokeColor);
              paint.setAlpha(bgStrokeAlphaValue);
              canvas->drawPath(bgStrokePath, paint);
          }

          fgStrokePath.addArc(rect, 0, 80);
          paint.setColor(strokeColor);
          canvas->drawPath(fgStrokePath, paint);
      }
  }
}

} // namespace react
} // namespace facebook
