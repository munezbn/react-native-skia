/*
* Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed uander the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/
#include <folly/dynamic.h>
#include <cxxreact/Instance.h>
#include <cxxreact/JsArgumentHelpers.h>
#include "ReactSkia/utils/RnsLog.h"
#include "NativeEventEmitter.h"

namespace facebook {
namespace react {
NativeEventEmitter::NativeEventEmitter(Instance* bridgeInstance):RSkBaseEventEmitter(bridgeInstance){
  if(bridgeInstance == nullptr){
    RNS_LOG_ERROR("bridgeInstance is the nullptr");
  }
}

NativeEventEmitter::~NativeEventEmitter() {
}

auto NativeEventEmitter::getMethods() -> std::vector<Method> {
  return {
    Method(
        "addListener",
        [&] (folly::dynamic args) {
          addListener(args[0].asString());
          setBridgeInstance(getInstance().lock().get());
        }),// end of addListener lambda

    Method(
        "removeListeners",
        [&] (folly::dynamic args) {
          int  removeCount = args[0].asInt();
          removeListeners(removeCount);
        }),
  };
}

void NativeEventEmitter::sendEventWithName(std::string eventName, folly::dynamic &&params, EmitterCompleteVoidCallback completeCallback){
  auto instance = getInstance().lock();
  if ( instance ) {
    setBridgeInstance(instance.get());
    RSkBaseEventEmitter::sendEventWithName(eventName, folly::dynamic(params),completeCallback);
  }
}

}//xplat
}//facebook
