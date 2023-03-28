/*
* Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/
#pragma once
#include <cxxreact/CxxModule.h>
#include "ReactSkia/utils/RnsUtils.h"
#include "BaseEventEmitter.h"

namespace facebook {
namespace react {
using namespace xplat;
using EmitterCompleteVoidCallback = std::function<void()>;
class NativeEventEmitter : public module::CxxModule, public RSkBaseEventEmitter{  
 public:
  NativeEventEmitter(Instance* bridgeInstance);
  ~NativeEventEmitter();
  auto getMethods() -> std::vector<Method>;
  void sendEventWithName(std::string eventName, folly::dynamic &&params, EmitterCompleteVoidCallback completeCallback=nullptr);
};
}//xplat
}//facebook
