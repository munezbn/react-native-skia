/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <react/renderer/components/view/ConcreteViewShadowNode.h>

#include "ActivityIndicatorProps.h"
#include "ActivityIndicatorState.h"

namespace facebook {
namespace react {

extern const char ActivityIndicatorComponentName[];

/*
 * `ShadowNode` for <ActivityIndicator> component.
 */
class ActivityIndicatorShadowNode final : public ConcreteViewShadowNode<
                                    ActivityIndicatorComponentName,
                                    ActivityIndicatorProps,
                                    ViewEventEmitter,
                                    ActivityIndicatorState> {

 public:
  using ConcreteViewShadowNode::ConcreteViewShadowNode;

  static ShadowNodeTraits BaseTraits() {
    auto traits = ConcreteViewShadowNode::BaseTraits();
    traits.set(ShadowNodeTraits::Trait::LeafYogaNode);
    return traits;
  }

  static ActivityIndicatorState initialStateData(
      ShadowNodeFragment const &fragment,
      ShadowNodeFamilyFragment const &familyFragment,
      ComponentDescriptor const &componentDescriptor) {
    return {};
  }

#pragma mark - LayoutableShadowNode

  void layout(LayoutContext layoutContext) override;

 private:
  void updateStateIfNeeded();
};

} // namespace react
} // namespace facebook