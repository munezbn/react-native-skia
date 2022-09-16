/*
 * Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "include/core/SkPaint.h"
#include "include/core/SkCanvas.h"
#include "include/effects/SkDashPathEffect.h"
#include <react/renderer/components/view/ViewProps.h>
#include "rns_shell/compositor/layers/Layer.h"

namespace facebook {
namespace react {

namespace RSkDrawUtils{

/*Function: Draw Background & Border */
  void drawBackground(SkCanvas *canvas,
                               Rect frame,
                               BorderMetrics borderMetrics,
                               SharedColor bgColor);
  void drawBorder(SkCanvas *canvas,
                               Rect frame,
                               BorderMetrics borderMetrics,
                               SharedColor bgColor);
  bool drawShadow(SkCanvas *canvas,
                               Rect frame,
                               BorderMetrics borderMetrics,
                               SharedColor bgColor,
                               struct RnsShell::shadowParams shadowParamsObj);
  void drawUnderline(SkCanvas *canvas,Rect frame,SharedColor underlineColor);
  bool isDrawVisible(SharedColor Color,Float thickness=1.0);
  void drawContentShadow(Rect frame,
                              SkCanvas *canvas,
                              SkPaint shadowPaint,
                              SkRect targetRect,
                              sk_sp<SkImage> imageData,
                              BorderMetrics imageBorderMetrics,
                              struct RnsShell::shadowParams shadowParamsObj);
}//namespace RSkDrawUtils
} // namespace react
} // namespace facebook
