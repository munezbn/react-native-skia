/*
* Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#include "sdk/KeyCodeMapping.h"
#include "sdk/NotificationCenter.h"
#include "core_modules/RSkEventEmitter.h"

namespace facebook {
namespace react {

class RSkTVNavigationEventEmitter final: public RSkEventEmitter {
    private:
        std::vector<std::string> events_ = {"onHWKeyEvent"};
        std::string tvEventName_ = "RCTTVNavigationEventNotification";
        unsigned int navEventId_ = UINT_MAX; // Some undefined ID

        void handleTVKeyEvent(key  eventKey, keyAction eventKeyAction);
        void handleTVNavigationEventNotification(folly::dynamic paramObject, NotificationCompleteVoidCallback completeCallback);

    public:
        RSkTVNavigationEventEmitter(
            const std::string &name, 
            std::shared_ptr<CallInvoker> jsInvoker,
            Instance *bridgeInstance);

        ~RSkTVNavigationEventEmitter() {}

        std::vector<std::string> supportedEvents() {
            return events_;
        }

        void startObserving();
        void stopObserving();
};

} //namespace react
} //namespace facebook
