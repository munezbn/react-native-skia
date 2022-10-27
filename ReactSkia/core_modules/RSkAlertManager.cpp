/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkAlertManager.h"
#include "utils/RnsLog.h"

namespace facebook {
namespace react {

struct AlertProps {
    std::string alertTitle;
    std::string alertMsg;
};

RSkAlertManager::RSkAlertManager(
    const std::string &name,
    std::shared_ptr<facebook::react::CallInvoker> jsInvoker,
    facebook::react::Instance *bridgeInstance)
    : TurboModule(name, jsInvoker) {
    methodMap_["alertWithArgs"] = MethodMetadata{2, alertWithArgsWrapper};
}

facebook::jsi::Value RSkAlertManager::alertWithArgsWrapper(
    facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const facebook::jsi::Value *args,
    size_t count) {
    
    if (count != 2) {
        return jsi::Value::undefined();
    }
    auto &self = static_cast<RSkAlertManager &>(turboModule);
    auto dataArg = facebook::jsi::dynamicFromValue(rt, args[0]); // Argument 1:: Alert Data
    // Argument 2:: Alert Callback
    struct AlertProps alertProps;
    alertProps.alertTitle.assign(dataArg["title"].getString()); 
    alertProps.alertMsg.assign(dataArg["message"].getString());
    
    RNS_LOG_DEBUG(" Alert Title   :: "<<alertProps.alertTitle.c_str());
    RNS_LOG_DEBUG(" Alert Message :: "<<alertProps.alertMsg.c_str());
    // Call the specific non-static Class object
    return self.processAlertMessages(alertProps);
}

jsi::Value RSkAlertManager::processAlertMessages(struct AlertProps &alertProps) {

    return jsi::Value::undefined();
}

}//react
}//facebook