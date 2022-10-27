/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

namespace rns {
namespace sdk {

// Dark Theme configuration
#define DARK_THEME_BACKGROUND_COLOR       SkColorSetARGB(0xFF, 0x34, 0x34, 0x34) //Dark Gray
#define DARK_THEME_FONT_COLOR             SK_ColorWHITE
// LIGHT Theme configuration
#define LIGHT_THEME_BACKGROUND_COLOR      SkColorSetARGB(0xFF, 0x80, 0x80, 0x80) // Mild Dark Tone on SK_ColorGRAY
#define LIGHT_THEME_FONT_COLOR            SK_ColorWHITE
//Default Text Configurations for "SCREEN RESOLUTION:720p"
#define SCREEN_RESOLUTION                 "720p"
#define TEXT_FONT_SIZE                    24
#define LINE_SPACING                      30

double getFontSizeForScreen(SkSize screenSize) {
  if(!strcmp(SCREEN_RESOLUTION,"720p")) {
    return TEXT_FONT_SIZE*(screenSize.width()/1280);
  }
}

double getLineSpacingForScreen(SkSize screenSize) {
  if(!strcmp(SCREEN_RESOLUTION,"720p")) {
    return TEXT_FONT_SIZE*(screenSize.height()/720);
  }
}

} // sdk
} // rns
