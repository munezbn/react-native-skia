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
#ifdef OS_LINUX
#include "SkAppUtil.h"
#endif

namespace sk_app {

Window::Window() {}

Window::~Window() {}

void Window::detach() { fWindowContext = nullptr; }

void Window::visitLayers(std::function<void(Layer*)> visitor) {
    for (int i = 0; i < fLayers.count(); ++i) {
        if (fLayers[i]->fActive) {
            visitor(fLayers[i]);
        }
    }
}

bool Window::signalLayers(std::function<bool(Layer*)> visitor) {
    for (int i = fLayers.count() - 1; i >= 0; --i) {
        if (fLayers[i]->fActive && visitor(fLayers[i])) {
            return true;
        }
    }
    return false;
}

void Window::onBackendCreated() {
    this->visitLayers([](Layer* layer) { layer->onBackendCreated(); });
}

void Window::onUIStateChanged(const SkString& stateName, const SkString& stateValue) {
    this->visitLayers([=](Layer* layer) { layer->onUIStateChanged(stateName, stateValue); });
}

void Window::onPaint() {
    if (!fWindowContext) {
        return;
    }
    sk_sp<SkSurface> backbuffer = fWindowContext->getBackbufferSurface();
    if (backbuffer == nullptr) {
        printf("no backbuffer!?\n");
        // TODO: try recreating testcontext
        return;
    }

    markInvalProcessed();

    // draw into the canvas of this surface
    this->visitLayers([](Layer* layer) { layer->onPrePaint(); });
    this->visitLayers([=](Layer* layer) { layer->onPaint(backbuffer.get()); });

    backbuffer->flushAndSubmit();

    fWindowContext->swapBuffers();
    didRenderFrame();
}

void Window::onResize(int w, int h) {
    if (!fWindowContext) {
        return;
    }
    fWindowContext->resize(w, h);
    this->visitLayers([=](Layer* layer) { layer->onResize(w, h); });
}

int Window::width() const {
    if (!fWindowContext) {
        return 0;
    }
    return fWindowContext->width();
}

int Window::height() const {
    if (!fWindowContext) {
        return 0;
    }
    return fWindowContext->height();
}

void Window::setRequestedDisplayParams(const DisplayParams& params, bool /* allowReattach */) {
    fRequestedDisplayParams = params;
    if (fWindowContext) {
        fWindowContext->setDisplayParams(fRequestedDisplayParams);
    }
}

int Window::sampleCount() const {
    if (!fWindowContext) {
        return 0;
    }
    return fWindowContext->sampleCount();
}

int Window::stencilBits() const {
    if (!fWindowContext) {
        return -1;
    }
    return fWindowContext->stencilBits();
}

GrDirectContext* Window::directContext() const {
    if (!fWindowContext) {
        return nullptr;
    }
    return fWindowContext->directContext();
}

void Window::inval() {
    if (!fWindowContext) {
        return;
    }
    if (!fIsContentInvalidated) {
        fIsContentInvalidated = true;
        onInval();
    }
}

void Window::markInvalProcessed() {
    fIsContentInvalidated = false;
}

}   // namespace sk_app
