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

/* Alert Window composed of below Internal Components in order::
1. Background
 ______________________________
|                              |
|   *************              |
|   |2. Title & Message        |
|   *************              |
|                              |
|      Will Grow Further       |
|______________________________|
*/


Alert* Alert::alertHandler_{nullptr};

Alert* Alert::getAlertHandler() {
  if(alertHandler_ == nullptr ) {
    alertHandler_ = new Alert();
  }
  return alertHandler_;
}

bool Alert::showAlert(alertInfo &alertData){

  Alert* alertHandle=Alert::getAlertHandler();

  alertHandle->addAlertToAlertList(alertData);

  if(alertHandle->alertWindowState_ == ALERT_WINDOW_DESTRUCTED) {
      // Create Sub Window for Alert
      alertHandle->alertWindowState_ = ALERT_WINDOW_ON_CREATION;
      alertHandle->createAlertWindow();
    } else {
      alertHandle->displayRecentAlert();
    }

  return true;//On Success
}

void Alert::displayRecentAlert() {

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
    triggerRenderRequest(ALERT_TITLE_AND_MESSAGE);
  }
}

inline void Alert::addAlertToAlertList(alertInfo &alertData) {
    std::lock_guard<std::mutex> lock(alertListAccessCtrlMutex_);

    alertInfoList_.push_back(alertData);
}

inline void Alert::removeAlertFromAlertList(unsigned int msgIndex) {

  std::lock_guard<std::mutex> lock(alertListAccessCtrlMutex_);

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

inline int Alert::getRecentAlertInfo(alertInfo &alertData) {
  std::lock_guard<std::mutex> lock(alertListAccessCtrlMutex_);
  if(alertInfoList_.empty()) {
    return -1;
  }
  alertData = alertInfoList_.back();
  return alertInfoList_.size();
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

  triggerRenderRequest(ALERT_BACKGROUND,true);//Batch this render call along with Below one
  triggerRenderRequest(ALERT_TITLE_AND_MESSAGE);
}

void Alert::createAlertWindow() {
  alertWindowSize_ = RnsShell::Window::getMainWindowSize();
  std::function<void()> createWindowCB = std::bind(&Alert::windowReadyToDrawCB, this);
  std::function<void(KeyInput)> windowKeyEventCB = std::bind( &Alert::onHWKeyHandler,this,
                                                      std::placeholders::_1);
  createWindow(alertWindowSize_, createWindowCB,windowKeyEventCB);
}

void Alert::onHWKeyHandler(KeyInput keyInput) {
  RNS_LOG_DEBUG("rnsKey: "<<RNSKeyMap[keyInput.key]<<" rnsKeyaction: "<<((keyInput.action ==0) ? "RNS_KEY_Press ": "RNS_KEY_Release ")<<"Key repeat : "<<keyInput.repeat);

  if ((keyInput.action != RNS_KEY_Press) || (RNS_KEY_Select != keyInput.key) || (keyInput.repeat) ) {
    return;
  }

  if(idOfMessageOnDisplay_ == -1) {
    return;// No Valid Index, nothing to remove from display
  }

  msgPendingToBeRemoved_=true;
  unsigned int msgIndex=idOfMessageOnDisplay_;
  removeAlertFromAlertList(msgIndex);
  msgPendingToBeRemoved_=false;

  displayRecentAlert();
}

inline void Alert::drawRecentAlertTitleAndMsg(std::vector<SkIRect> &dirtyRect) {

  alertInfo alertRef;
  int alertIndex= getRecentAlertInfo(alertRef);
  if((alertIndex == -1) || (ALERT_WINDOW_ACTIVE != alertWindowState_)) {
    return;
  }

  double drawStartPointX{0},drawStartPointY{0};

  if (!alertRef.alertTitle.empty()) {

    double titleWidth=font_.measureText( alertRef.alertTitle.c_str(),
                                         alertRef.alertTitle.length(),
                                         SkTextEncoding::kUTF8);
    drawStartPointX=(alertWindowSize_.width() - titleWidth)/2;
    drawStartPointY=(alertWindowSize_.height() - textFontSize_) / 2;

    pictureCanvas_->drawSimpleText(
                              alertRef.alertTitle.c_str(),
                              alertRef.alertTitle.length(),
                              SkTextEncoding::kUTF8,
                              drawStartPointX,
                              drawStartPointY,
                              font_,
                              paint_);
    setWindowTittle(alertRef.alertTitle.c_str());

    dirtyRect.push_back(SkIRect::MakeXYWH(drawStartPointX,drawStartPointY,
                               titleWidth,textFontSize_));

    RNS_LOG_DEBUG(" drawAlert Title :: "<<alertRef.alertTitle.c_str());
  }

  if (!alertRef.alertMessage.empty()) {

    double messageWidth=font_.measureText( alertRef.alertMessage.c_str(),
                                         alertRef.alertMessage.length(),
                                         SkTextEncoding::kUTF8);
    drawStartPointY += textFontSize_ + lineSpacing_;
    drawStartPointX=(alertWindowSize_.width() - messageWidth)/2;

    pictureCanvas_->drawSimpleText(
                            alertRef.alertMessage.c_str(),
                            alertRef.alertMessage.length(),
                            SkTextEncoding::kUTF8,
                            drawStartPointX,
                            drawStartPointY,
                            font_,
                            paint_);

    dirtyRect.push_back(SkIRect::MakeXYWH(drawStartPointX,drawStartPointY,
                               messageWidth,textFontSize_));
    RNS_LOG_DEBUG(" drawAlert Msg :: "<<alertRef.alertMessage.c_str());
  }

  idOfMessageOnDisplay_=alertIndex;

}

void Alert::triggerRenderRequest(AlertComponents components,bool batchRenderRequest) {
  std::scoped_lock lock(alertActiontCtrlMutex_);
  SkPictureRecorder pictureRecorder_;
  std::string commandKey;
  std::vector<SkIRect>   dirtyRect;
  pictureCanvas_ = pictureRecorder_.beginRecording(SkRect::MakeXYWH(0, 0, alertWindowSize_.width(), alertWindowSize_.height()));
  bool invalidateFlag{true}; //to be set to indicate static or dynamic component.
  switch(components) {
    case ALERT_BACKGROUND:
      pictureCanvas_->clear(DARK_THEME_BACKGROUND_COLOR);
      dirtyRect.push_back(SkIRect::MakeXYWH(0, 0, alertWindowSize_.width(), alertWindowSize_.height()));
      commandKey="AlertBackGround";
      invalidateFlag=false;
    break;
    case ALERT_TITLE_AND_MESSAGE:
      drawRecentAlertTitleAndMsg(dirtyRect);
      commandKey="AlertTitleAndMessage";
      break;
    default:
    break;
  }

  auto pic = pictureRecorder_.finishRecordingAsPicture();
  if(pic.get()) {
    RNS_LOG_DEBUG("SkPicture For " << commandKey << " :Command Count: " <<
    pic.get()->approximateOpCount() << " operations and size : " << pic.get()->approximateBytesUsed() <<
    " Dirty Rect Count : "<<dirtyRect.size());
  }
  if(ALERT_WINDOW_ACTIVE == alertWindowState_) {
    commitDrawCall(commandKey,{dirtyRect,pic,invalidateFlag},batchRenderRequest);
  }
}

}//sdk
}//rns
