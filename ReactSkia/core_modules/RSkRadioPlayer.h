/*
* Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "core_modules/RSkEventEmitter.h"

using namespace std;
namespace facebook {
namespace react {

class RSkRadioPlayer : public RSkEventEmitter {
 public:
  RSkRadioPlayer(const std::string &name,
            std::shared_ptr<CallInvoker> jsInvoker,
            Instance *bridgeInstance);

  ~RSkRadioPlayer();

  static jsi::Value tune(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count);
  static jsi::Value play(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count);
  static jsi::Value stop(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count);
  static jsi::Value setVolume(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count);
  static jsi::Value setMuteStatus(jsi::Runtime &rt,
        TurboModule &turboModule,
        const jsi::Value *args,
        size_t count);

  void startObserving() {};
  void stopObserving() {};

 private:

  jsi::Value nativeRadioTune();
  jsi::Value nativeRadioPlay();
  jsi::Value nativeRadioStop();
};

}//namespace react
}//namespace facebook
