/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 * Copyright (C) Munez BN munezbn.dev@gmail.com
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include "ReactSkia/utils/RnsUtils.h"

#if ENABLE(RNS_DISPLAY_REFRESH_MONITOR)
#include "rns_shell/compositor/DisplayRefreshMonitor.h"
#else
#include "ReactSkia/utils/RnsJsRaf.h"
#endif
#include "rns_shell/compositor/layers/Layer.h"
#include "ReactSkia/components/RSkComponentActivityIndicator.h"

namespace facebook {
namespace react {

class RSkComponentActivityIndicatorManager {
 public:
  static RSkComponentActivityIndicatorManager *getActivityIndicatorManager();

  void addComponent(std::weak_ptr<RSkComponent> candidate);
  void removeComponent(Tag tag);
  ~RSkComponentActivityIndicatorManager();
  
 private:
  static RSkComponentActivityIndicatorManager *activityIndicatorManager_;
  std::vector<std::weak_ptr<RSkComponent>> actIndComponentList_;
#if ENABLE(RNS_DISPLAY_REFRESH_MONITOR)
  std::shared_ptr<DisplayRefreshMonitorClient> rafMonitor_;
#else
  RnsJsRequestAnimation * animRequest_{nullptr};
#endif

  RSkComponentActivityIndicatorManager();
  void handleActivityIndicatorAnimation(double timestamp);
};

} // namespace react
} // namespace facebook
