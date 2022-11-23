/*
 * Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <ReactSkia/activityindicator/react/renderer/components/activityindicator/ActivityIndicatorProps.h>
#include "ReactSkia/components/RSkComponentActivityIndicator.h"

#include "ReactSkia/utils/RnsLog.h"

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

  /*Yet to implement the activity indicator drawings...*/
}

} // namespace react
} // namespace facebook
