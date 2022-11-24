/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

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
