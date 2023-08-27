/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 * Copyright (C) Munez BN munezbn.dev@gmail.com
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <sstream>

#include "ReactSkia/utils/RnsLog.h"

#include "platform/linux/TaskLoop.h"
#include "DisplayRefreshMonitor.h"

namespace RnsShell {

#define RNS_DISPLAY_REFRESH_CALLBACK_PREFIX "__rnsOnDisplayRefreshCallback"

DisplayRefreshMonitor* DisplayRefreshMonitor::sharedDisplayRefreshMonitor_{nullptr};
std::mutex DisplayRefreshMonitor::mutex_;

DisplayRefreshMonitor::DisplayRefreshMonitor(DisplayRefreshMonitor::Delegator& delegator)
    : delegator_(delegator) {}

DisplayRefreshMonitor* DisplayRefreshMonitor::create(DisplayRefreshMonitor::Delegator& delegator) {
  if (sharedDisplayRefreshMonitor_ == nullptr) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (sharedDisplayRefreshMonitor_ == nullptr) {
      sharedDisplayRefreshMonitor_ = new DisplayRefreshMonitor(delegator);
    }
  }
  return sharedDisplayRefreshMonitor_;
}

DisplayRefreshMonitor* DisplayRefreshMonitor::sharedMonitor() {
  if(sharedDisplayRefreshMonitor_ == nullptr) {
    RNS_LOG_ERROR("DisplayRefreshMonitor has not been created yet by compositor....");
  }
  return sharedDisplayRefreshMonitor_;
}

void DisplayRefreshMonitor::displayRefreshCallback(double timeStamp) {
  // TODO this must be called in main thread only, so need to add assert if it is not called in main thread
  std::vector<std::shared_ptr<DisplayRefreshMonitorClient>> rafCallbacks;
  // Add all valid callbacks to a temporary list to avoid deadlock in case a callback calls add/remove of a client.
  {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& rafClientWeak : clientList_) {
      std::shared_ptr<DisplayRefreshMonitorClient> rafClient = rafClientWeak.second.lock();
      if(rafClient && rafClient->callback_)
        rafCallbacks.push_back(rafClient);
    }
  }
  if(rafCallbacks.size() > 0) {
    for (auto& callbackClient : rafCallbacks) {
      if(callbackClient->callback_)
        callbackClient->callback_(timeStamp);
    }
    delegator_.handleDisplayRefreshMonitorUpdate(); // Flush the render tree. No need to lock because this function is supposed to be called in main thread only.
  }
}

bool DisplayRefreshMonitor::requiresDisplayRefreshCallback() {
  RNS_LOG_TRACE("Has RAF Clients " << hasClients());
  return hasClients();
}

void DisplayRefreshMonitor::dispatchDisplayRefreshCallback() {
  if(hasClients()) {
    TaskLoop::main().dispatch([&]() { // Schedule callbacks on MAIN renderer thread
      displayRefreshCallback(SkTime::GetMSecs());
    });
  }
}

// DisplayRefreshMonitorClient

uint64_t DisplayRefreshMonitorClient::nextUniqueId() {
  static std::atomic<uint64_t> nextId(1);
  uint64_t id;
  do {
    id = nextId.fetch_add(1);
  } while (id == 0);  // 0 invalid id.
  return id;
}

DisplayRefreshMonitorClient::DisplayRefreshMonitorClient(DisplayRefreshCallback callback)
    : callback_(callback){
  std::ostringstream ss;
  ss << RNS_DISPLAY_REFRESH_CALLBACK_PREFIX << nextUniqueId();
  clientId_ = ss.str();
  return;
}

std::shared_ptr<DisplayRefreshMonitorClient> DisplayRefreshMonitor::createClient(DisplayRefreshCallback callback) {
  return std::make_shared<DisplayRefreshMonitorClient>(callback);
}

void DisplayRefreshMonitor::addClient(std::weak_ptr<DisplayRefreshMonitorClient> clientWeak) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto rafClient = clientWeak.lock();
  if(rafClient == nullptr)
    return;
  clientList_[rafClient->id()] = clientWeak;
}

bool DisplayRefreshMonitor::removeClient(std::weak_ptr<DisplayRefreshMonitorClient> clientWeak) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto rafClient = clientWeak.lock();
  if(rafClient == nullptr)
    return false;

  std::string rafClientId = rafClient->id();
  RnsRefresMonitorClientList &tempList = clientList_;
  auto it = tempList.find(rafClientId);
  if (it != tempList.end()) {
    tempList.erase(rafClientId);
  }
  return true;
}

} // namespace RnsShell
