 /*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#ifndef OSK_H
#define OSK_H

#include <semaphore.h>

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"

#include "rns_shell/compositor/Compositor.h"
#include "rns_shell/common/Window.h"
#include "rns_shell/platform/graphics/PlatformDisplay.h"
#include "rns_shell/platform/graphics/WindowContextFactory.h"

#include "NotificationCenter.h"
#include "RNSKeyCodeMapping.h"

//Types of Suported KeyBoard
enum OSKTypes {
    OSK_DEFAULT_TYPE,
    OSK_ALPHA_NUMERIC_KB=OSK_DEFAULT_TYPE,
    OSK_NUMERIC_KB,
    OSK_TYPE_END
};
//Suported Themes
enum OSKThemes {
    OSK_DEFAULT_THEME,
    OSK_DARK_THEME=OSK_DEFAULT_THEME,
    OSK_LIGHT_THEME
};
enum KBLayoutType {
    ALPHA_LOWERCASE_LAYOUT,
    ALPHA_UPPERCASE_LAYOUT,
    SYMBOL_LAYOUT,
    NUMERIC_LAYOUT
};

enum keyType {
    TOGGLE_KEY ,
    TEXT_KEY,
    FUNCTION_KEY,
    KEY_TYPE_COUNT
};

//Configuration to be specified while OSK Launch
struct OSKConfig {
    OSKTypes        oskType;
    OSKThemes       oskTheme;
    const char *    placeHolderName;
    const char *    returnKeyLabel;
    bool      enablesReturnKeyAutomatically;
};

// Default OSKConfig
static OSKConfig defaultOSKConfig={ OSK_DEFAULT_TYPE, OSK_DEFAULT_THEME, nullptr, "done", false };

typedef struct keyPosition {
    SkPoint        textXY{}; // text X,Y to draw
    SkPoint        textHLXY{}; // font's X,Y to draw
    SkPoint        textCapsHLXY{}; // font's X,Y to draw
    SkRect         highlightTile; // Area to highlight on Key Focus
}keyPosition_t;

typedef struct KeyInfo {
    const char *   keyName;
    rnsKey         keyValue;
    keyType        keyType;
    unsigned int   KBPartitionId;
}KeyInfo_t;

typedef struct KeySiblingInfo {
    SkPoint siblingRight;
    SkPoint siblingLeft;
    SkPoint siblingUp;
    SkPoint siblingDown;
}keySiblingInfo_t;

typedef struct keyPlacementConfig {
    SkPoint groupOffset;
    SkPoint groupKeySpacing;
    float   hlTileFontSizeMultiplier;
    float   fontScaleFactor;
    unsigned int maxTextLength;
}keyPlacementConfig_t;

typedef std::vector<std::vector<KeyInfo_t>> KBLayoutKeyInfoContainer;
typedef std::vector<std::vector<keyPosition_t>> KBLayoutKeyPosContainer;
typedef std::vector<std::vector<keySiblingInfo_t>> KBLayoutSibblingInfoContainer;


struct OSKLayout {
    KBLayoutKeyInfoContainer*  keyInfo;
    KBLayoutKeyPosContainer*    keyPos;
    KBLayoutSibblingInfoContainer*    siblingInfo;
    keyPlacementConfig_t*          KBGroupConfig;
    KBLayoutType      KBLayoutType;
    unsigned int      textFontSize;
    unsigned int      textHLFontSize;
    SkPoint           defaultFocussIndex;
};

class OnScreenKeyboard {
    public:
        OnScreenKeyboard(OSKConfig oskConfig,SkSize ScreenSize);
        static OnScreenKeyboard* launch(OSKConfig oskConfig=defaultOSKConfig);// Interface to launch OSK
        void exit(); //Interface to quit OSK
    private:
        void createOSKLayout(OSKTypes KBtype );
        void onHWkeyHandler(rnsKey key, rnsKeyAction eventKeyAction);
        void onExposeHandler(RnsShell::Window* window);
        void highlightFocussedKey(SkPoint index);
        void handleSelection();
        void drawOSK(OSKTypes oskType);
        void drawPlaceHolder();
        void drawFont(SkPoint index,SkColor color,bool onHLTile=false);
        void drawOSKPartition();
        void pushToDisplay();
// Maintainables
        unsigned int exposeEventID_{-1};
        OSKConfig     oskConfig_;
        std::unique_ptr<RnsShell::Window> OSKwindow_;
        std::unique_ptr<RnsShell::WindowContext> OSKwindowContext_;
        sem_t semReadyToDraw;
        sk_sp<SkSurface> backBuffer_;
        SkCanvas *OSKcanvas_=nullptr;
        unsigned int OSKeventId_{-1};
        SkSize        ScreenSize{0,0};
        bool          generateOSKLayout{true};
        SkPoint       focussedKey_{0};
        SkPoint       lastFocussedKey_{0};
        OSKLayout     oskLayout_;
        SkColor       bgColor_{SK_ColorWHITE};
        SkColor       fontColor_{SK_ColorWHITE};
};
#endif //OSK_H

