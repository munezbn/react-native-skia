/*
* Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "Alert.h"

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
}

bool Alert::showAlert(alertInfo &alertData){
	Alert* alertHnadle=Alert::getAlertHandler();
	return true;//On Success
}
}//sdk
}//rns
