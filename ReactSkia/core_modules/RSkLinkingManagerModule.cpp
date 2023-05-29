/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/core_modules/RSkLinkingManagerModule.h"
#include "ReactSkia/utils/RnsLog.h"

namespace facebook {
namespace react {

RSkLinkingManagerModule::RSkLinkingManagerModule(
  const std::string &name,
  std::shared_ptr<react::CallInvoker> jsInvoker,
  react::Instance *bridgeInstance)
    : RSkEventEmitter(name, jsInvoker, bridgeInstance) {
  methodMap_["getInitialURL"] = MethodMetadata {0, getInitialURLWrapper};
  methodMap_["canOpenURL"] = MethodMetadata {1, canOpenURLWrapper};
  methodMap_["openURL"] = MethodMetadata {1, openURLWrapper};
  methodMap_["openSettings"] = MethodMetadata {0, openSettingsWrapper};
}

jsi::Value RSkLinkingManagerModule::getInitialURLWrapper(
  jsi::Runtime &rt,
  TurboModule &turboModule,
  const jsi::Value *args,
  size_t count) {

  if (count != 0) {
    return jsi::Value::undefined();
  }
  auto &self = static_cast<RSkLinkingManagerModule &>(turboModule);
  return self.getInitialURL(rt);
}

jsi::Value RSkLinkingManagerModule::canOpenURLWrapper(
  jsi::Runtime &rt,
  TurboModule &turboModule,
  const jsi::Value *args,
  size_t count) {

  RNS_LOG_NOT_IMPL;
  if (count != 1) {
    return jsi::Value::undefined();
  }
  return jsi::Value::undefined();
}


jsi::Value RSkLinkingManagerModule::openURLWrapper(
  jsi::Runtime &rt,
  TurboModule &turboModule,
  const jsi::Value *args,
  size_t count) {

  RNS_LOG_NOT_IMPL;
  if (count != 1) {
    return jsi::Value::undefined();
  }
  return jsi::Value::undefined();
}

jsi::Value RSkLinkingManagerModule::openSettingsWrapper(
  jsi::Runtime &rt,
  TurboModule &turboModule,
  const jsi::Value *args,
  size_t count) {

  RNS_LOG_NOT_IMPL;
  if (count != 0) {
    return jsi::Value::undefined();
  }
  return jsi::Value::undefined();
}

jsi::Value RSkLinkingManagerModule::getInitialURL(jsi::Runtime &rt) {
  RNS_LOG_NOT_IMPL;
  return jsi::Value::undefined();
}

void RSkLinkingManagerModule::startObserving() {RNS_LOG_NOT_IMPL;}
void RSkLinkingManagerModule::stopObserving() {RNS_LOG_NOT_IMPL;}

} // react
} // facebook

