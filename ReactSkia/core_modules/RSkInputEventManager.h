/*
 * Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#pragma once
#include <semaphore.h>
#include "sdk/ThreadSafeQueue.h"
#include "ReactSkia/core_modules/RSkSpatialNavigator.h"

using namespace rns::sdk;

namespace facebook {
namespace react {

using namespace SpatialNavigator;

class RSkInputEventManager {
 private:
  static RSkInputEventManager *sharedInputEventManager_;
  RSkInputEventManager();

#if ENABLE(FEATURE_KEY_THROTTLING)
  void inputWorkerThreadFunction();
  std::unique_ptr<ThreadSafeQueue<KeyInput>> keyQueue_;
  sem_t keyEventPost_;
  std::thread inputWorkerThread_;
  std::atomic<int> activeInputClients_ {0};
#endif
  void processKey(KeyInput &keyInput);
  RSkSpatialNavigator* spatialNavigator_ {nullptr};

 public:
  ~RSkInputEventManager();
  static RSkInputEventManager* getInputKeyEventManager();
  void keyHandler(KeyInput keyInput);
#if ENABLE(FEATURE_KEY_THROTTLING)
  void onEventEmit();
  void onEventComplete();
#endif

#if defined(TARGET_OS_TV) && TARGET_OS_TV
  void sendNotificationWithEventType(std::string eventType, int tag, rnsKeyAction keyAction = RNS_KEY_UnknownAction, NotificationCompleteVoidCallback completeCallback = nullptr);
#endif //TARGET_OS_TV

  NotificationCompleteVoidCallback completeCallback_ {nullptr};
};

} // namespace react
} // namespace facebook
