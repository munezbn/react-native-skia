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

static key previousKey{KEY_UnKnown};
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

void Window::onKey(key eventKey, keyAction eventKeyAction){
    Inputkeyinfo keyInfo(eventKey,eventKeyAction);
    if(previousKey == eventKey  && eventKeyAction == KEY_Press){
      keyInfo.repeat = true;
    } else { keyInfo.repeat = false;}
    if(eventKeyAction == KEY_Release) {
      previousKey=KEY_UnKnown;
    } else {previousKey=eventKey;}

#if ENABLE(FEATURE_ONSCREEN_KEYBOARD)
    if(winType == SubWindow)
        NotificationCenter::subWindowCenter().emit("onHWKeyEvent", keyInfo);
    else
#endif/*FEATURE_ONSCREEN_KEYBOARD*/
        NotificationCenter::defaultCenter().emit("onHWKeyEvent", keyInfo);
    return;
}

GrDirectContext* Window::directContext() const {
    RNS_LOG_NOT_IMPL;
    return nullptr;
}

}   // namespace RnsShell
