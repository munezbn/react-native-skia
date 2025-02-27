/*
 * Copyright 2016 Google Inc.
 * Copyright (C) 1994-2021 OpenTV, Inc. and Nagravision S.A.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef RasterWindowContextX11_DEFINED
#define RasterWindowContextX11_DEFINED

#include "include/core/SkSurface.h"
#include "WindowContextFactory.h"
#include "RasterWindowContext.h"

typedef Window XWindow;
using sk_app::window_context_factory::UnixWindowInfo;

namespace sk_app {

class RasterWindowContextX11 : public RasterWindowContext {
public:
    RasterWindowContextX11(const UnixWindowInfo&, const DisplayParams&);

    sk_sp<SkSurface> getBackbufferSurface() override;
    void swapBuffers() override;
    bool isValid() override { return SkToBool(fWindow); }
    void resize(int  w, int h) override;
    void setDisplayParams(const DisplayParams& params) override;

protected:
    sk_sp<SkSurface> fBackbufferSurface;
    Display* fDisplay;
    XWindow  fWindow;
    GC       fGC;
    typedef RasterWindowContext INHERITED;
};

}   // namespace sk_app

#endif //RasterWindowContextX11_DEFINED
