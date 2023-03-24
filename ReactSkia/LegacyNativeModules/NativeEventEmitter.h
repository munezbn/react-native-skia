/*
* Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/
#pragma once
#include <cxxreact/CxxModule.h>
#include "ReactSkia/utils/RnsUtils.h"


namespace facebook {
namespace xplat {
class NativeEventEmitter : public module::CxxModule{
 private:
  int  listenerCount_= 0;
  virtual void startObserving() = 0;
  virtual void stopObserving() = 0;
 public:
  NativeEventEmitter();
  ~NativeEventEmitter();
  void sendEventWithName(std::string eventName, folly::dynamic eventData);
  auto getMethods() -> std::vector<Method>;
};
}//xplat
}//facebook
