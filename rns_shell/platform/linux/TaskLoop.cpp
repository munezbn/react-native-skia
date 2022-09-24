/*
* Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#include "TaskLoop.h"
#include "ReactSkia/utils/RnsLog.h"

namespace RnsShell {

static std::unique_ptr<TaskLoop> mainTaskRunner_;

TaskLoop::TaskLoop() {
  RNS_LOG_INFO("TaskLopp created");
}

TaskLoop::~TaskLoop() {
}

bool TaskLoop::running() {
    return eventBase_.isRunning();
}

void TaskLoop::run() {
    eventBase_.loopForever();
}

void TaskLoop::waitUntilRunning() {
    eventBase_.waitUntilRunning();
}

void TaskLoop::stop(){
    eventBase_.terminateLoopSoon();
}

TaskLoop& TaskLoop::main() {
    return *mainTaskRunner_;
}

void TaskLoop::dispatch(Func fun) {
    if(eventBase_.isRunning())
        eventBase_.runInEventBaseThread(std::move(fun));
    else
        RNS_LOG_ERROR("TaskLoop eventBase is not running!!");
}

void TaskLoop::initializeMain() {
    if(mainTaskRunner_.get() == nullptr)
        mainTaskRunner_ = std::make_unique<TaskLoop>();
}

}   // namespace RnsShell
