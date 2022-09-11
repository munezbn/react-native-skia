 /*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "KeyCodeMapping.h"

namespace rns {
namespace sdk {

/*
Position Configuration mentioned in this file should be for 1280*720 screen.
For other Screen Size, it will be scaled accordingly in SW w.r.t 1280*720.
*/
static SkSize baseScreenSize{1280,720};

#define LOWER_TO_UPPER_CASE_OFFSET 32

//Max Partition or Group, OSK Layout can Handle. Each Group Get it function/Purpose w.r.t Layout.
enum partitionID {
  GROUP1,
  GROUP2,
  GROUP3,
  GROUP4,
  MAX_GROUP=GROUP4
};

/* KeyBoard Layout for Alpha Numeric KeyBoard */

#define ALPHA_NUMERIC_KB_PARTITION_COUNT   4
SkPoint alphaNumericKBReturnKeyIndex{13,2};/*KeyIndex,RowIndex*/
SkPoint alphaNumericKBDefaultHLKeyIndex{7,0};/*KeyIndex,RowIndex*/
KBLayoutKeyPosContainer alphaNumericKBKeyPos;
KBLayoutSibblingInfoContainer alphaNumericKBKeySiblingInfo;
KBLayoutKeyInfoContainer alphaNumericKBKeyInfo= {
  //row 1
  {
    {"123ABC",KEY_UnKnown,KEY_TYPE_TOGGLE,GROUP1},
    {"1",KEY_1,KEY_TYPE_TEXT,GROUP2},
    {"2",KEY_2,KEY_TYPE_TEXT,GROUP2},
    {"3",KEY_3,KEY_TYPE_TEXT,GROUP2},
    {"a",KEY_a,KEY_TYPE_TEXT,GROUP3},
    {"b",KEY_b,KEY_TYPE_TEXT,GROUP3},
    {"c",KEY_c,KEY_TYPE_TEXT,GROUP3},
    {"d",KEY_d,KEY_TYPE_TEXT,GROUP3},
    {"e",KEY_e,KEY_TYPE_TEXT,GROUP3},
    {"f",KEY_f,KEY_TYPE_TEXT,GROUP3},
    {"g",KEY_g,KEY_TYPE_TEXT,GROUP3},
    {"h",KEY_h,KEY_TYPE_TEXT,GROUP3},
    {"i",KEY_i,KEY_TYPE_TEXT,GROUP3},
    {"space",KEY_Space,KEY_TYPE_FUNCTION,GROUP4}
  },
   //row 2
  {
    {"123abc",KEY_UnKnown,KEY_TYPE_TOGGLE,GROUP1},
    {"4",KEY_4,KEY_TYPE_TEXT,GROUP2},
    {"5",KEY_5,KEY_TYPE_TEXT,GROUP2},
    {"6",KEY_6,KEY_TYPE_TEXT,GROUP2},
    {"j",KEY_j,KEY_TYPE_TEXT,GROUP3},
    {"k",KEY_k,KEY_TYPE_TEXT,GROUP3},
    {"l",KEY_l,KEY_TYPE_TEXT,GROUP3},
    {"m",KEY_m,KEY_TYPE_TEXT,GROUP3},
    {"n",KEY_n,KEY_TYPE_TEXT,GROUP3},
    {"o",KEY_o,KEY_TYPE_TEXT,GROUP3},
    {"p",KEY_p,KEY_TYPE_TEXT,GROUP3},
    {"q",KEY_q,KEY_TYPE_TEXT,GROUP3},
    {"r",KEY_r,KEY_TYPE_TEXT,GROUP3},
    {"delete",KEY_Delete,KEY_TYPE_FUNCTION,GROUP4}
  },
  {
  //row 3
    {"@?#",KEY_UnKnown,KEY_TYPE_TOGGLE,GROUP1},
    {"7",KEY_7,KEY_TYPE_TEXT,GROUP2},
    {"8",KEY_8,KEY_TYPE_TEXT,GROUP2},
    {"9",KEY_9,KEY_TYPE_TEXT,GROUP2},
    {"s",KEY_s,KEY_TYPE_TEXT,GROUP3},
    {"t",KEY_t,KEY_TYPE_TEXT,GROUP3},
    {"u",KEY_u,KEY_TYPE_TEXT,GROUP3},
    {"v",KEY_v,KEY_TYPE_TEXT,GROUP3},
    {"w",KEY_w,KEY_TYPE_TEXT,GROUP3},
    {"x",KEY_x,KEY_TYPE_TEXT,GROUP3},
    {"y",KEY_y,KEY_TYPE_TEXT,GROUP3},
    {"z",KEY_z,KEY_TYPE_TEXT,GROUP3},
    {".",KEY_Period,KEY_TYPE_TEXT,GROUP3},
    {"return",KEY_Select,KEY_TYPE_FUNCTION,GROUP4}
  },
  {
    //row 4
    {"-",KEY_Minus,KEY_TYPE_TEXT,GROUP2},
    {"0",KEY_0,KEY_TYPE_TEXT,GROUP2},
    {"_",KEY_Underscore,KEY_TYPE_TEXT,GROUP2 },
    {"!",KEY_Exclam,KEY_TYPE_TEXT,GROUP3},
    {"@",KEY_At,KEY_TYPE_TEXT,GROUP3 },
    {"#",KEY_Numbersign,KEY_TYPE_TEXT,GROUP3},
    {"?",KEY_Question,KEY_TYPE_TEXT,GROUP3},
    {"*",KEY_Asterisk,KEY_TYPE_TEXT,GROUP3},
    {",",KEY_Comma,KEY_TYPE_TEXT,GROUP3},
    {";",KEY_Semicolon,KEY_TYPE_TEXT,GROUP3},
    {"right", KEY_Right,KEY_TYPE_FUNCTION,GROUP3},
    {"left", KEY_Left,KEY_TYPE_FUNCTION,GROUP3}
  }
};

keyPlacementConfig_t alphaNumericKBGroupConfig[ALPHA_NUMERIC_KB_PARTITION_COUNT]={
  //GROUP1-Toggle key
  {{20,60},{15,30},1.3,0.75,4},
  //GROUP2-Numeric key
  {{150,40},{15,15},1.25,1,1},
  //GROUP3-Alpha & SYmbol key
  {{320,40},{15,15},1.25,1,1},
  //GROUP4-Function key
  {{820,50},{15,15},1.5,1,1}
};

/* KeyBoard Layout for Symbol Key Board */

KBLayoutSibblingInfoContainer symbolKBKBKeySiblingInfo;
KBLayoutKeyPosContainer symbolKBKBKeyPos;
#define SYMBOL_KB_PARTITION_COUNT 3
SkPoint symbolKBReturnKeyIndex{11,2};/*KeyIndex,RowIndex*/
SkPoint symbolKBDefaultHLKeyIndex{7,0};/*KeyIndex,RowIndex*/
KBLayoutKeyInfoContainer symbolKBKBKeyInfo={
  {
    {"123ABC",KEY_UnKnown,KEY_TYPE_TOGGLE,GROUP1},
    {"!",KEY_Exclam,KEY_TYPE_TEXT,GROUP2},
    {"@",KEY_At,KEY_TYPE_TEXT,GROUP2},
    {"#",KEY_Numbersign,KEY_TYPE_TEXT,GROUP2},
    {"$",KEY_Dollar,KEY_TYPE_TEXT,GROUP2},
    {"^",KEY_Asciicircum,KEY_TYPE_TEXT,GROUP2},
    {"&",KEY_Ampersand,KEY_TYPE_TEXT,GROUP2},
    {"*",KEY_Asterisk,KEY_TYPE_TEXT,GROUP2},
    {"~",KEY_Asciitilde,KEY_TYPE_TEXT,GROUP2},
    {"(",KEY_ParenLeft,KEY_TYPE_TEXT,GROUP2},
    {")",KEY_ParenRight,KEY_TYPE_TEXT,GROUP2},
    {",",KEY_Comma,KEY_TYPE_TEXT,GROUP2},
    {".",KEY_Period,KEY_TYPE_TEXT,GROUP2},
    {"space",KEY_Space,KEY_TYPE_FUNCTION,GROUP3}
  },
  {
   //row 2
    {"123abc",KEY_UnKnown,KEY_TYPE_TOGGLE,GROUP1},
    {";",KEY_Semicolon,KEY_TYPE_TEXT,GROUP2},
    {":",KEY_Colon,KEY_TYPE_TEXT,GROUP2},
    {"|",KEY_Bar,KEY_TYPE_TEXT,GROUP2},
    {"\\",KEY_BackSlash,KEY_TYPE_TEXT,GROUP2 },
    {"/",KEY_Shash,KEY_TYPE_TEXT,GROUP2},
    {"{",KEY_BraceLeft,KEY_TYPE_TEXT,GROUP2},
    {"}",KEY_BraceRight,KEY_TYPE_TEXT,GROUP2},
    {"[",KEY_BracketLeft,KEY_TYPE_TEXT,GROUP2},
    {"]",KEY_BracketRight,KEY_TYPE_TEXT,GROUP2},
    {"`",KEY_Grave,KEY_TYPE_TEXT,GROUP2},
    {"'",KEY_Apostrophe,KEY_TYPE_TEXT,GROUP2},
    {"_",KEY_Underscore,KEY_TYPE_TEXT,GROUP2},
    {"delete",KEY_Delete,KEY_TYPE_FUNCTION,GROUP3}
  },
  {
  //row 3
    {"@?#",KEY_UnKnown ,KEY_TYPE_TOGGLE,GROUP1},
    {"%",KEY_Percent,KEY_TYPE_TEXT,GROUP2},
    {">",KEY_Greater,KEY_TYPE_TEXT,GROUP2},
    {"<",KEY_Less,KEY_TYPE_TEXT,GROUP2},
    {"?",KEY_Question,KEY_TYPE_TEXT,GROUP2},
    {"\"",KEY_Quotedbl,KEY_TYPE_TEXT,GROUP2},
    {"=",KEY_Equal,KEY_TYPE_TEXT,GROUP2},
    {"+",KEY_Plus,KEY_TYPE_TEXT,GROUP2},
    {"-",KEY_Minus,KEY_TYPE_TEXT,GROUP2},
    {"right", KEY_Right,KEY_TYPE_FUNCTION,GROUP2},
    {"left", KEY_Left,KEY_TYPE_FUNCTION,GROUP2},
    {"return",KEY_Select,KEY_TYPE_FUNCTION,GROUP3},
  }
};

keyPlacementConfig_t symbolKBGroupConfig[SYMBOL_KB_PARTITION_COUNT]={
  //GROUP1-Toggle key
  {{20,60},{15,30},1.3,0.75,4},
  //GROUP2-Symbol key
  {{150,40},{15,25},1.3,1,1},
  //GROUP3-Function key
  {{820,50},{30,15},1.5,1,1}
};

/* KeyBoard Layout for Numeric Key Board */

KBLayoutSibblingInfoContainer numericKBKeySiblingInfo;
KBLayoutKeyPosContainer numericKBKeyPos;
#define NUMERIC_KB_PARTITION_COUNT 1
SkPoint  numericKBReturnKeyIndex{3,3};/*KeyIndex,RowIndex*/
SkPoint numericKBDefaultHLKeyIndex{2,0};/*KeyIndex,RowIndex*/
KBLayoutKeyInfoContainer numericKBKeyKeyInfo={
  {
    //row 1
    {"1",KEY_1,KEY_TYPE_TEXT,GROUP1},
    {"2",KEY_2,KEY_TYPE_TEXT,GROUP1},
    {"3",KEY_3,KEY_TYPE_TEXT,GROUP1},
    {"-",KEY_Underscore,KEY_TYPE_TEXT,GROUP1}
  },
  {
    //row 2
    {"4",KEY_4,KEY_TYPE_TEXT,GROUP1},
    {"5",KEY_5,KEY_TYPE_TEXT,GROUP1},
    {"6",KEY_6,KEY_TYPE_TEXT,GROUP1},
    {"space",KEY_Space,KEY_TYPE_FUNCTION,GROUP1}
  },
  {
    //row 3
    {"7",KEY_7,KEY_TYPE_TEXT,GROUP1},
    {"8",KEY_8,KEY_TYPE_TEXT,GROUP1},
    {"9",KEY_9,KEY_TYPE_TEXT,GROUP1},
    {"delete",KEY_Delete,KEY_TYPE_FUNCTION,GROUP1}
  },
  {
    //row 4
    {",",KEY_Comma,KEY_TYPE_TEXT,GROUP1},
    {"0",KEY_0,KEY_TYPE_TEXT,GROUP1},
    {".",KEY_Period,KEY_TYPE_TEXT,GROUP1 },
    {"return",KEY_Select,KEY_TYPE_FUNCTION,GROUP1}
  }
};

keyPlacementConfig_t numericKBGroupConfig[NUMERIC_KB_PARTITION_COUNT] = {
  {{250,30},{40,40},1.3,1.5,1}
};


typedef std::map<std::string,KBLayoutType> ToggleKeyMap;

ToggleKeyMap toggleKeyMap = {
  {"123ABC",ALPHA_UPPERCASE_LAYOUT},
  {"123abc",ALPHA_LOWERCASE_LAYOUT},
  {"@?#",SYMBOL_LAYOUT}
};

typedef struct unicharFontConfig {
  unsigned int unicharValue;
  float fontScaleFactor;
}UnicharFontConfig_t;

typedef std::map<std::string,UnicharFontConfig_t> FunctionKeyMap;

FunctionKeyMap functionKeyMap = {
  {"delete",{0x232B,1}},
  {"space",{0x23B5,2}},
  {"return",{0x23CE,1.5}}, // default return key entry: "enter"
  {"enter",{0x23CE,1.5}},
  {"search",{0x2315,2.5}},
  {"right",{0x25BA,1}},
  {"left",{0x25c4,1}}
};

} // namespace sdk
} // namespace rns


