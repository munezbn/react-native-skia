/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <react/renderer/components/view/ViewProps.h>

namespace facebook {
namespace react {

// TODO (T28334063): Consider for codegen.
class ActivityIndicatorProps final : public ViewProps {
 public:
  ActivityIndicatorProps() = default;
  ActivityIndicatorProps(const ActivityIndicatorProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props
  bool animating{true};
  SharedColor color{};
  bool hidesWhenStopped{true};
  std::string const size{};
};

} // namespace react
} // namespace facebook
