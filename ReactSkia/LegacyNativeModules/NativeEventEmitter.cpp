/*
* Copyright (C) 1994-2023 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed uander the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/
#include <folly/dynamic.h>
#include <cxxreact/Instance.h>
#include <cxxreact/JsArgumentHelpers.h>

#include "NativeEventEmitter.h"

namespace facebook {
namespace xplat {

NativeEventEmitter::NativeEventEmitter() {}

NativeEventEmitter::~NativeEventEmitter() {
}


auto NativeEventEmitter::getMethods() -> std::vector<Method> {
  return {
    Method(
        "addListener",
        [&] (folly::dynamic args) {
          RNS_LOG_DEBUG("addListener args "<< args[0]);
          listenerCount_++;
          if (listenerCount_ == 1) {
            startObserving();
          }
        }),// end of addListener lambda

    Method(
        "removeListeners",
        [&] (folly::dynamic args) {
          RNS_LOG_DEBUG(" removeListeners args "<< args[0]<<" listenerCount_ "<<listenerCount_);
          int  removeCount = args[0].asInt();;
          listenerCount_ = std::max(listenerCount_ - removeCount, 0);
          if (listenerCount_ == 0) {
            stopObserving();
          }
        }),
  };
}

void NativeEventEmitter::sendEventWithName(std::string eventName, folly::dynamic eventData) {
  auto instance = getInstance().lock();
  if ( instance ) {
    instance->callJSFunction(
            "RCTDeviceEventEmitter", "emit",
            (eventData != nullptr) ?
            folly::dynamic::array(folly::dynamic::array(eventName),eventData):
            folly::dynamic::array(eventName));
  }
}


}//xplat
}//facebook
