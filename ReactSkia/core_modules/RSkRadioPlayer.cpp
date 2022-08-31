/*
* Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/
#include "include/core/SkImage.h"

#include <cxxreact/JsArgumentHelpers.h>

#include "ReactSkia/components/RSkComponentImage.h"
#include "ReactSkia/sdk/CurlNetworking.h"
#include "ReactSkia/utils/RnsLog.h"
#include "RSkRadioPlayer.h"

using namespace folly;

namespace facebook {
namespace react {

RSkRadioPlayer::RSkRadioPlayer(
  const std::string &name,
  std::shared_ptr<CallInvoker> jsInvoker,
  Instance *bridgeInstance)
  : RSkEventEmitter(name, jsInvoker, bridgeInstance) {
    methodMap_["tune"] = MethodMetadata{0, tune};
    methodMap_["play"] = MethodMetadata{0, play};
    methodMap_["stop"] = MethodMetadata{0, stop};
    methodMap_["setVolume"] = MethodMetadata{1, setVolume};
    methodMap_["mute"] = MethodMetadata{1, setMuteStatus};
}

RSkRadioPlayer::~RSkRadioPlayer() {
}

jsi::Value RSkRadioPlayer::tune(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count) {
  RNS_LOG_TODO("RadioPlayerModule tune API");
  auto &self = static_cast<RSkRadioPlayer &>(turboModule);
  return self.nativeRadioTune();
}

jsi::Value RSkRadioPlayer::play(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count) {
  RNS_LOG_TODO("RadioPlayerModule play API");
  auto &self = static_cast<RSkRadioPlayer &>(turboModule);
  return self.nativeRadioPlay();
}

jsi::Value RSkRadioPlayer::stop(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count) {
  RNS_LOG_TODO("RadioPlayerModule stop API");
  auto &self = static_cast<RSkRadioPlayer &>(turboModule);
  return self.nativeRadioStop();
}

jsi::Value RSkRadioPlayer::setVolume(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count) {
  RNS_LOG_TODO("RadioPlayerModule setVolume:" << args[0].getNumber());
  return jsi::Value::undefined();
}

jsi::Value RSkRadioPlayer::setMuteStatus(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count) {
  RNS_LOG_TODO("RadioPlayerModule setMute:" << args[0].getBool());
  return jsi::Value::undefined();
}

jsi::Value RSkRadioPlayer::nativeRadioTune() {
  dynamic metaDataInfo = dynamic::object();
  metaDataInfo["trackName"] = "TestTrackName";
  metaDataInfo["artistName"] = "TestArtistName";

  RNS_LOG_INFO("Send MetadataDidChange event");
  sendEventWithName("MetadataDidChange",dynamic(metaDataInfo));
  return jsi::Value::undefined();
}

jsi::Value RSkRadioPlayer::nativeRadioPlay() {
  dynamic metaDataInfo = dynamic::object();
  metaDataInfo["state"] = "playing";

  RNS_LOG_INFO("Send StateDidChange event");
  sendEventWithName("StateDidChange",dynamic(metaDataInfo));
  return jsi::Value::undefined();
}

jsi::Value RSkRadioPlayer::nativeRadioStop() {
  dynamic metaDataInfo = dynamic::object();
  metaDataInfo["state"] = "stopped";

  RNS_LOG_INFO("Send StateDidChange event");
  sendEventWithName("StateDidChange",dynamic(metaDataInfo));
  return jsi::Value::undefined();
}

}// namespace react
}//namespace facebook
