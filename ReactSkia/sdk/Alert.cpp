/*
* Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "Alert.h"
#include "NotificationCenter.h"

namespace rns {
namespace sdk {

Alert* Alert::alertHandler_{nullptr};
std::mutex Alert::mutex_;

Alert* Alert::getAlertHandler() {
  std::lock_guard<std::mutex> lock(mutex_);
  if(alertHandler_ == nullptr ) {
    alertHandler_ = new Alert();
  }
  return alertHandler_;
}

Alert::Alert(){
  // Create Sub Window for Alert
  createAlertWindow();
}

bool Alert::showAlert(alertInfo &alertData){
  Alert* alertHnadle=Alert::getAlertHandler();
  return true;//On Success
}

void Alert::windowReadyToDrawCB() {
  alertWindowState_ = ALERT_WINDOW_ACTIVE;
  setWindowTittle("Alert Window");
}

void Alert::createAlertWindow() {
  alertWindowSize_ = RnsShell::Window::getMainWindowSize();
  std::function<void()> createWindowCB = std::bind(&Alert::windowReadyToDrawCB, this);
  std::function<void()> forceFullScreenDrawCB = std::bind(&Alert::drawAlert, this);
  createWindow(alertWindowSize_, createWindowCB, forceFullScreenDrawCB);

  if (subWindowKeyEventId_ == -1) {
    std::function<void(rnsKey, rnsKeyAction)> handler = std::bind( &Alert::onHWKeyHandler,this,
                                std::placeholders::_1,  // KeyValue
                                std::placeholders::_2);  // eventKeyAction
    subWindowKeyEventId_ = NotificationCenter::subWindowCenter().addListener("onHWKeyEvent", handler);
  }
}

void Alert::onHWKeyHandler(rnsKey keyValue,rnsKeyAction eventKeyAction) {
  if ((eventKeyAction != RNS_KEY_Press) ) {
    return;
  }
  RNS_LOG_DEBUG("KEY RECEIVED : " << RNSKeyMap[keyValue]);
  if (RNS_KEY_Select == keyValue) {

  }
}

void Alert::drawAlert() {

}

}//sdk
}//rns
