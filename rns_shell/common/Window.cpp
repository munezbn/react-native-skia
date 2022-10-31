/*
* Copyright 2016 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#include "Window.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"

#include "WindowContext.h"

#include "ReactSkia/sdk/NotificationCenter.h"

namespace RnsShell {

Window::Window() {}

Window::~Window() {}

void Window::setRequestedDisplayParams(const DisplayParams& params, bool /* allowReattach */) {
    requestedDisplayParams_ = params;
}

int Window::sampleCount() const {
    RNS_LOG_NOT_IMPL;
    return 0;
}

int Window::stencilBits() const {
    RNS_LOG_NOT_IMPL;
    return 0;
}

void Window::onResize(int w, int h) {
    RNS_LOG_NOT_IMPL;
}

GrDirectContext* Window::directContext() const {
    RNS_LOG_NOT_IMPL;
    return nullptr;
}

void Window::onKey(rnsKey eventKeyType, rnsKeyAction eventKeyAction){
#if ENABLE(FEATURE_ONSCREEN_KEYBOARD)
    if(winType == SubWindow) {
        NotificationCenter::subWindowCenter().emit("onHWKeyEvent", eventKeyType, eventKeyAction,this);
    } else
#endif/*FEATURE_ONSCREEN_KEYBOARD*/
    {
        NotificationCenter::defaultCenter().emit("onHWKeyEvent", eventKeyType, eventKeyAction);
    }
    return;
}

}   // namespace RnsShell
