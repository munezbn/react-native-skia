/*
* Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <mutex>

#include "RNSKeyCodeMapping.h"
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

    static Alert* getAlertHandler(); // Interface to Instantiate & get Alert singleton class object
    static bool showAlert(alertInfo &alertData);

  private:
    enum AlertWindowState {
      ALERT_WINDOW_CREATED, // Window is Created
      ALERT_WINDOW_ACTIVE, // Window is Active
      ALERT_WINDOW_INACTIVE, // Window is In-Active
      ALERT_WINDOW_DESTRUCTED // Window is Destructed
    };

    static Alert* alertHandler_;
    static std::mutex mutex_;
    SkSize alertWindowSize_;
    int subWindowKeyEventId_{-1};
    AlertWindowState alertWindowState_{ALERT_WINDOW_DESTRUCTED};

    Alert();
    ~Alert(){};

    void windowReadyToDrawCB();
    void createAlertWindow();
    void onHWKeyHandler(rnsKey key, rnsKeyAction eventKeyAction);
    void drawAlert();
};

}//sdk
}//rns
