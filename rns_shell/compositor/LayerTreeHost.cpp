/*
* Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
* Copyright (C) Munez BN munezbn.dev@gmail.com
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#include "Window.h"
#include "LayerTreeHost.h"
#include "rns_shell/common/Application.h"

namespace RnsShell {

LayerTreeHost::LayerTreeHost(Application& app)
    : app_(app),
      window_(Window::createNativeWindow(&PlatformDisplay::sharedDisplayForCompositing())),
      compositorClient_(*this),
      displayID_(std::numeric_limits<uint32_t>::max() - app_.identifier()) {
  SkSize viewPort(SkSize::MakeEmpty());
  compositor_ = Compositor::create(compositorClient_, compositorClient_, displayID_, viewPort);
}

LayerTreeHost::~LayerTreeHost() {
  //TODO cancel Pending schedules
  compositor_->invalidate();
  compositor_.reset();
  window_ = nullptr;
}

uint64_t LayerTreeHost::nativeSurfaceHandle() {
  return window_->nativeWindowHandle();
}

void LayerTreeHost::didRenderFrame() {
  if(window_)
    window_->didRenderFrame();
}

void LayerTreeHost::sizeDidChange(SkSize& size) {
  compositor_->setViewportSize(size);
}

void LayerTreeHost::begin() {
  compositor_->begin();
}

#if ENABLE(RNS_DISPLAY_REFRESH_MONITOR)
void LayerTreeHost::handleDisplayRefreshMonitorUpdate() {
  // TODO this must be called from main thread for now, so by default passing true
  commitScene(true);
}
#endif

void LayerTreeHost::commitScene(bool immediate) {
  // TODO Check compositor state idle, progress, scheduled
  compositor_->commit(immediate);
}

void LayerTreeHost::setRootCompositingLayer(SharedLayer rootLayer) {
  compositor_->setRootLayer(rootLayer);
}

}   // namespace RnsShell
