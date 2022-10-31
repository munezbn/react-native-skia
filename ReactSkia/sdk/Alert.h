/*
* Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <atomic>
#include <mutex>

#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkFont.h"
#include "third_party/skia/include/core/SkFontMgr.h"

#include "KeyCodeMapping.h"
#include "WindowDelegator.h"

namespace rns {
namespace sdk {

class Alert : public WindowDelegator {

  public :
    struct AlertInfo {
      std::string alertTitle;
      std::string alertMsg;
    };
    typedef struct AlertInfo alertInfo;
    enum AlertAction {
      SHOW_ALERT,
      REMOVE_ALERT
    };

    static Alert* getAlertHandler(); // Interface to Instantiate & get Alert singleton class object
    static bool showAlert(alertInfo &alertData);

  private:
    enum AlertWindowState {
      ALERT_WINDOW_ON_CREATION, // Window getting Created
      ALERT_WINDOW_ACTIVE, // Window created & ready To draw
      ALERT_WINDOW_DESTRUCTED // Window Destroyed
    };

    std::list<alertInfo> alertInfoList_;
    static Alert* alertHandler_;
    static std::mutex alertThreadRaceHandlerMutex_;
    std::mutex msgHandlerMutex_;
    SkSize alertWindowSize_;
    unsigned int idOfMessageOnDisplay_{0};
    std::atomic<bool> msgPendingToBeRemoved_{false};
    AlertWindowState alertWindowState_{ALERT_WINDOW_DESTRUCTED};
    double textFontSize_;
    double lineSpacing_;
    SkFont font_;
    SkPaint paint_;

    Alert()=default;
    ~Alert()=default;

    void windowReadyToDrawCB();
    void createAlertWindow();
    void onHWKeyHandler(rnsKey key, rnsKeyAction eventKeyAction);
    inline void drawRecentAlert();
    void handleAlertMsg();
    inline void PopFromAlertContainer(unsigned int msgIndex);
};

}//sdk
}//rns
