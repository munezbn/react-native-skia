/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 * Copyright (C) Munez BN munezbn.dev@gmail.com
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include<iostream>
#include <map>
#include "ReactSkia/utils/RnsUtils.h"

#ifndef RNS_ANIMATION_FRAME_RATE
#define RNS_ANIMATION_FRAME_RATE 60
#endif
#define RNS_ANIMATION_FRAME_RATE_THROTTLE     ((1/RNS_ANIMATION_FRAME_RATE)) //Milliseconds

namespace RnsShell {

class DisplayRefreshMonitorClient;

using DisplayRefreshCallback = std::function<void(double)>;
using RnsRefresMonitorClientList = std::map<std::string, std::weak_ptr<DisplayRefreshMonitorClient>>;

class DisplayRefreshMonitorClient {
 public:
  DisplayRefreshMonitorClient(DisplayRefreshCallback callback);
  ~DisplayRefreshMonitorClient(){}

  void start();
  void stop();

  static uint64_t nextUniqueId();
  std::string id() { return clientId_; }
  bool isActive() { return isActive_; }
  void setActive(bool active) { isActive_ = active; }

  const DisplayRefreshCallback callback_ {nullptr};
 private:
  std::atomic<bool> isActive_{false};
  std::string clientId_;
};

class DisplayRefreshMonitor {
 public:

  class Delegator {
   public:
    virtual void notifyDisplayRefreshMonitorUpdate() = 0;
    virtual void handleDisplayRefreshMonitorUpdate() = 0;
  };

  static DisplayRefreshMonitor* create(DisplayRefreshMonitor::Delegator& delegator);
  static DisplayRefreshMonitor* sharedMonitor();
  virtual ~DisplayRefreshMonitor(){};

  std::shared_ptr<DisplayRefreshMonitorClient> createClient(DisplayRefreshCallback callback);
  bool hasClients() const { return clientList_.size(); }
  void addClient(std::weak_ptr<DisplayRefreshMonitorClient> client);
  bool removeClient(std::weak_ptr<DisplayRefreshMonitorClient> client);

  bool requiresDisplayRefreshCallback();
  void dispatchDisplayRefreshCallback();
 private :
  static DisplayRefreshMonitor *sharedDisplayRefreshMonitor_;
  static std::mutex mutex_;
  DisplayRefreshMonitor(Delegator&);
  DisplayRefreshMonitor(DisplayRefreshMonitor&) = delete;
  void displayRefreshCallback(double timestamp);

  Delegator& delegator_;
  RnsRefresMonitorClientList clientList_;
};

} // namespace RnsShell
