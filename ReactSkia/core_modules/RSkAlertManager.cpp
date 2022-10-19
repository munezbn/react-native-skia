/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/core_modules/RSkAlertManager.h"
#include "ReactSkia/sdk/sdkStylesConfig.h"

namespace facebook {
namespace react {

/* Alert Window composed of below Internal Components in order::
1. Background 
 ______________________________
|                              |
|   *************              |
|   |2. Title   |              |
|   *************              |
|   ************               |
|   |3. Message|               |
|   ************               |
|                              |
|      Will Grow Further       |
|______________________________|

*/

std::mutex lockMsgDrawing;

#define FONT_SIZE 24
#define LINE_SPACE 14
#define OFFSET_VERTICAL 30

RSkAlertManager::RSkAlertManager(
    const std::string &name,
    std::shared_ptr<facebook::react::CallInvoker> jsInvoker,
    facebook::react::Instance *bridgeInstance)
    : TurboModule(name, jsInvoker) {
  methodMap_["alertWithArgs"] = MethodMetadata{1, alertWithArgsWrapper};
}

void RSkAlertManager::processAlertMessages(std::shared_ptr<Alert> alertPtr) {
  std::vector<SkIRect> dirtyRect;

  alertPropsList_.push_back(alertPtr);
  if (ALERT_WINDOW_DESTRUCT == alertWindowState_) {
    alertWindowState_ = ALERT_WINDOW_CREATE;
    createAlertWindow();
  } else {
    if (ALERT_WINDOW_ACTIVE == alertWindowState_) {
        {
          drawAlertMsg();
        }

    }
  }
}

facebook::jsi::Value RSkAlertManager::alertWithArgsWrapper(
    facebook::jsi::Runtime &rt,
    TurboModule &turboModule,
    const facebook::jsi::Value *args,
    size_t count) {
  auto &alertManagerInstance = static_cast<RSkAlertManager &>(turboModule);
  auto alertProps = facebook::jsi::dynamicFromValue(rt, args[0]);
  alertManagerInstance.processAlertMessages(std::make_shared<Alert>(
      alertProps["title"].getString(), alertProps["message"].getString()));

  return 0;
}

void RSkAlertManager::drawAlertMsg() {
  std::scoped_lock lock(lockMsgDrawing);
  if (alertPropsList_.empty() || (ALERT_WINDOW_ACTIVE != alertWindowState_)) {
    RNS_LOG_INFO("Return From draw Alert Msg without drawing Alert Message!!!");
    return;
  }
  RNS_LOG_ERROR("drawAlertMsg=== @ ");
  RNS_LOG_ERROR("processAlertMessages=== ");
  std::vector<SkIRect> dirtyRect;

  double titleWidth, messageWidth;
  double drawStartPointX, drawStartPointY;
  std::shared_ptr<Alert> alertRef = alertPropsList_.back();
  titleWidth = font_.measureText(
      alertRef->getTitle().c_str(),
      strlen(alertRef->getTitle().c_str()),
      SkTextEncoding::kUTF8);

  if (!alertPropsList_.empty()) {
      SkPictureRecorder pictureRecorder_;

      pictureCanvas_ = pictureRecorder_.beginRecording(SkRect::MakeXYWH(0, 0, mainWindowSize_.width(), mainWindowSize_.height()));

    pictureCanvas_->clear(DARK_THEME_BACKGROUND_COLOR);

    drawStartPointX = (mainWindowSize_.width() - titleWidth) / 2;
    drawStartPointY = (mainWindowSize_.height() - FONT_SIZE) / 2;
    pictureCanvas_->drawSimpleText(
        alertRef->getTitle().c_str(),
        strlen(alertRef->getTitle().c_str()),
        SkTextEncoding::kUTF8,
        drawStartPointX,
        drawStartPointY,
        font_,
        paint_);

    dirtyRect.push_back(SkIRect::MakeXYWH(drawStartPointX, drawStartPointY-FONT_SIZE, titleWidth, FONT_SIZE+OFFSET_VERTICAL));

    drawStartPointY = ((mainWindowSize_.height() - FONT_SIZE) / 2) + (FONT_SIZE) + OFFSET_VERTICAL;
    if (alertRef->getMessage().c_str() != NULL) {
      pictureCanvas_->drawSimpleText(
        alertRef->getMessage().c_str(),
        strlen(alertRef->getMessage().c_str()),
        SkTextEncoding::kUTF8,
        drawStartPointX,
        drawStartPointY,
        font_,
        paint_);
    }
    dirtyRect.push_back(SkIRect::MakeXYWH(drawStartPointX, drawStartPointY-FONT_SIZE, mainWindowSize_.width(), FONT_SIZE+OFFSET_VERTICAL));
    RNS_LOG_ERROR("drawAlertMsg=== EXIT");
    auto pic = pictureRecorder_.finishRecordingAsPicture();
    commitDrawCall("Title AND MSG",{dirtyRect,pic});
  }
  displayMsgIndex_ = alertPropsList_.size();

}

void RSkAlertManager::windowReadyToDrawCB() {
{
  std::scoped_lock lock(lockMsgDrawing);
  alertWindowState_ = ALERT_WINDOW_ACTIVE;
  SkPictureRecorder pictureRecorder_;
  setBasePicCommand("BackGround");

  pictureCanvas_ = pictureRecorder_.beginRecording(SkRect::MakeXYWH(0, 0, mainWindowSize_.width(), mainWindowSize_.height()));
  pictureCanvas_->clear(DARK_THEME_BACKGROUND_COLOR);
  auto pic = pictureRecorder_.finishRecordingAsPicture();
  std::vector<SkIRect> dirtyRect;
  dirtyRect.push_back(SkIRect::MakeXYWH(0, 0, mainWindowSize_.width(), mainWindowSize_.height()));
  commitDrawCall("BackGround",{dirtyRect,pic});
}
{
    RNS_LOG_ERROR("windowReadyToDrawCB=== @ ");

  drawAlertMsg();
}
}

void RSkAlertManager::createAlertWindow() {
  mainWindowSize_ = RnsShell::Window::getMainWindowSize();
  std::function<void()> createWindowCB =
      std::bind(&RSkAlertManager::windowReadyToDrawCB, this);
  setWindowTittle("Alert Window!!!");
  createWindow(mainWindowSize_, createWindowCB);
  if (subWindowKeyEventId_ == -1) {
    std::function<void(rnsKey, rnsKeyAction, RnsShell::Window*)> handler =
        std::bind(
            &RSkAlertManager::onHWKeyHandler,
            this,
            std::placeholders::_1,  // KeyValue
            std::placeholders::_2,  // eventKeyAction
            std::placeholders::_3); // Window
    subWindowKeyEventId_ = NotificationCenter::subWindowCenter().addListener("onHWKeyEvent", handler);
  }
  font_.setSize(FONT_SIZE);
  paint_.setColor(DARK_THEME_FONT_COLOR);
}

void RSkAlertManager::onHWKeyHandler(
    rnsKey keyValue,
    rnsKeyAction eventKeyAction,
    RnsShell::Window *window) {
  if ((eventKeyAction != RNS_KEY_Press) || (getWindow() != window)) {
    return;
  }
  std::vector<SkIRect> dirtyRect;

  RNS_LOG_INFO("KEY RECEIVED : " << RNSKeyMap[keyValue]);

  if (RNS_KEY_Select == keyValue) {
    if ((alertPropsList_.size() == displayMsgIndex_)) {
      alertPropsList_.pop_back();
      if (alertPropsList_.empty()) {
        if (subWindowKeyEventId_ != -1) {
          NotificationCenter::subWindowCenter().removeListener(
              subWindowKeyEventId_);
          subWindowKeyEventId_ = -1;
        }
        closeWindow();
        alertWindowState_ = ALERT_WINDOW_DESTRUCT;

        return;
      }

      {
        drawAlertMsg();
      }

    } else {
      std::list<std::shared_ptr<Alert>>::iterator it = alertPropsList_.begin();
      std::advance(it, displayMsgIndex_);
      alertPropsList_.erase(it);
    }
  }
}
} // namespace react
} // namespace facebook
