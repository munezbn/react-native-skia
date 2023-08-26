/*
* Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
* Copyright (C) Munez BN munezbn.dev@gmail.com
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/
#pragma once

#include "PlatformDisplay.h"
#include "Compositor.h"

namespace RnsShell {
class Application;
class Window;

class LayerTreeHost {
 public:

  LayerTreeHost(Application& client);
  virtual ~LayerTreeHost();

  void setRootCompositingLayer(SharedLayer rootLayer);
  void begin();
  void commitScene(bool immediate);
  void sizeDidChange(SkSize& size);
#if ENABLE(RNS_DISPLAY_REFRESH_MONITOR)
  void handleDisplayRefreshMonitorUpdate();
#endif

  PlatformDisplayID displayID() const { return displayID_; }
  Compositor* compositor() { return compositor_.get(); }

 private:
  class CompositorClient : public Compositor::Client, public DisplayRefreshMonitor::Delegator {
    RNS_MAKE_NONCOPYABLE(CompositorClient);

   public:
    CompositorClient(LayerTreeHost& layerTreeHost)
        : layerTreeHost_(layerTreeHost) { }
    ~CompositorClient(){};

   private:
    uint64_t nativeSurfaceHandle() override { return layerTreeHost_.nativeSurfaceHandle(); }
    void notifyDisplayRefreshMonitorUpdate() override {layerTreeHost_.begin();}
    void handleDisplayRefreshMonitorUpdate() override {layerTreeHost_.handleDisplayRefreshMonitorUpdate();}

    void didRenderFrame() override { layerTreeHost_.didRenderFrame(); }
    LayerTreeHost& layerTreeHost_;
  };

  uint64_t nativeSurfaceHandle();
  void didRenderFrame();

  Application& app_;
  std::unique_ptr<Window> window_;
  CompositorClient compositorClient_;
  std::unique_ptr<Compositor> compositor_;
  PlatformDisplayID displayID_;
};

}   // namespace RnsShell
