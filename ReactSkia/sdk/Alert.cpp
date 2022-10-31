/*
* Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/


#include "Alert.h"
#include "NotificationCenter.h"
#include "sdkStyleConfig.h"

namespace rns {
namespace sdk {

Alert* Alert::alertHandler_{nullptr};
std::mutex Alert::alertThreadRaceHandlerMutex_;

Alert* Alert::getAlertHandler() {
  if(alertHandler_ == nullptr ) {
    alertHandler_ = new Alert();
  }
  return alertHandler_;
}

bool Alert::showAlert(alertInfo &alertData){

  std::lock_guard<std::mutex> lock(alertThreadRaceHandlerMutex_);

  Alert* alertHnadle=Alert::getAlertHandler();

  alertHnadle->alertInfoList_.push_back(alertData);

  if(alertHnadle->alertWindowState_ == ALERT_WINDOW_DESTRUCTED) {
    // Create Sub Window for Alert
    alertHnadle->alertWindowState_ = ALERT_WINDOW_ON_CREATION;
    alertHnadle->createAlertWindow();
  } else if (alertHnadle->alertWindowState_ == ALERT_WINDOW_ACTIVE){
    alertHnadle->handleAlertMsg();
  }
  return true;//On Success
}

void Alert::handleAlertMsg() {

  if((alertWindowState_ != ALERT_WINDOW_ACTIVE) || msgPendingToBeRemoved_) {
    return;
  }

  std::lock_guard<std::mutex> lock(msgHandlerMutex_);

  if (alertInfoList_.empty()) {
// Close Window , When No Message Left
    closeWindow();
    alertWindowState_=ALERT_WINDOW_DESTRUCTED;
  } else {
// Else Present Latest Alert Message
    if (ALERT_WINDOW_ACTIVE == alertWindowState_) {
      drawRecentAlert();
      commitDrawCall();
    }
  }
}

inline void Alert::PopFromAlertContainer(unsigned int msgIndex) {

  if(alertInfoList_.empty() || (msgIndex > alertInfoList_.size())) {
    return;
  }
  if(alertInfoList_.size() == idOfMessageOnDisplay_) {
    // Current Alert Message is the Latest Message
    alertInfoList_.pop_back();
  } else {
    //New Alert Message Pending to be displayed
    std::list<alertInfo>::iterator it = alertInfoList_.begin();
    std::advance(it, msgIndex);
    alertInfoList_.erase(it);
  }
}

void Alert::windowReadyToDrawCB() {

  setWindowTittle("Alert Window");

//Get Darw Parameters for screen Size
  textFontSize_=TEXT_FONT_SIZE*(alertWindowSize_.width()/DEFAULT_SCREEN_WIDTH);
  lineSpacing_=LINE_SPACING*(alertWindowSize_.height()/DEFAULT_SCREEN_HEIGHT);
  font_.setSize(textFontSize_);
  paint_.setColor(DARK_THEME_FONT_COLOR);
  paint_.setAntiAlias(true);

  alertWindowState_ = ALERT_WINDOW_ACTIVE;
  handleAlertMsg();
}

void Alert::createAlertWindow() {
  alertWindowSize_ = RnsShell::Window::getMainWindowSize();
  std::function<void()> createWindowCB = std::bind(&Alert::windowReadyToDrawCB, this);
  std::function<void()> forceFullScreenDrawCB = std::bind(&Alert::drawRecentAlert, this);
  std::function<void(rnsKey, rnsKeyAction)> windowKeyEventCB = std::bind( &Alert::onHWKeyHandler,this,
                                std::placeholders::_1,  // KeyValue
                                std::placeholders::_2);  // eventKeyAction
  createWindow(alertWindowSize_, createWindowCB, forceFullScreenDrawCB,windowKeyEventCB);
}

void Alert::onHWKeyHandler(rnsKey keyValue,rnsKeyAction eventKeyAction) {
  RNS_LOG_DEBUG("KEY RECEIVED : " << RNSKeyMap[keyValue]);
  if ((eventKeyAction != RNS_KEY_Press) || (RNS_KEY_Select != keyValue) ) {
    return;
  }
  msgPendingToBeRemoved_=true;
  unsigned int msgIndex=idOfMessageOnDisplay_;

  std::lock_guard<std::mutex> lock(alertThreadRaceHandlerMutex_);

  PopFromAlertContainer(msgIndex);
  msgPendingToBeRemoved_=false;
  handleAlertMsg();
}

inline void Alert::drawRecentAlert() {
  if (alertInfoList_.empty() || (ALERT_WINDOW_ACTIVE != alertWindowState_)) {
    return;
  }

  double drawStartPointX{0},drawStartPointY{0};
  alertInfo alertRef=alertInfoList_.back();

  windowDelegatorCanvas->clear(DARK_THEME_BACKGROUND_COLOR);

  if (!alertRef.alertTitle.empty()) {

    double titleWidth=font_.measureText( alertRef.alertTitle.c_str(),
                                         alertRef.alertTitle.length(),
                                         SkTextEncoding::kUTF8);
    drawStartPointX=(alertWindowSize_.width() - titleWidth)/2;
    drawStartPointY=(alertWindowSize_.height() - textFontSize_) / 2;

    windowDelegatorCanvas->drawSimpleText(
                              alertRef.alertTitle.c_str(),
                              alertRef.alertTitle.length(),
                              SkTextEncoding::kUTF8,
                              drawStartPointX,
                              drawStartPointY,
                              font_,
                              paint_);
    setWindowTittle(alertRef.alertTitle.c_str());
    RNS_LOG_DEBUG(" drawAlert Title :: "<<alertRef.alertTitle.c_str());
  }

  if (!alertRef.alertMsg.empty()) {

    double messageWidth=font_.measureText( alertRef.alertMsg.c_str(),
                                         alertRef.alertMsg.length(),
                                         SkTextEncoding::kUTF8);
    drawStartPointY += textFontSize_ + lineSpacing_;
    drawStartPointX=(alertWindowSize_.width() - messageWidth)/2;

    windowDelegatorCanvas->drawSimpleText(
                            alertRef.alertMsg.c_str(),
                            alertRef.alertMsg.length(),
                            SkTextEncoding::kUTF8,
                            drawStartPointX,
                            drawStartPointY,
                            font_,
                            paint_);
    RNS_LOG_DEBUG(" drawAlert Msg :: "<<alertRef.alertMsg.c_str());
  }
  idOfMessageOnDisplay_ = alertInfoList_.size();

}

}//sdk
}//rns
