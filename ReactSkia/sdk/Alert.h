/*
* Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <mutex>

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

    static Alert* alertHandler_;
    static std::mutex mutex_;

    Alert();
    ~Alert(){};

};

}//sdk
}//rns
