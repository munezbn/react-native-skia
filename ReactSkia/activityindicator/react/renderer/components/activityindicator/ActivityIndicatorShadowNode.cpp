/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <react/renderer/core/LayoutContext.h>

#include "ActivityIndicatorShadowNode.h"

namespace facebook {
namespace react {

char const ActivityIndicatorComponentName[] = "ActivityIndicatorView";

void ActivityIndicatorShadowNode::updateStateIfNeeded() {
  ensureUnsealed();

  auto state =
      ActivityIndicatorState {};
  setStateData(std::move(state));
}

#pragma mark - LayoutableShadowNode

void ActivityIndicatorShadowNode::layout(LayoutContext layoutContext) {
  updateStateIfNeeded();
  ConcreteViewShadowNode::layout(layoutContext);
}

} // namespace react
} // namespace facebook