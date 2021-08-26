#ifndef RNS_KEYCODE_MAPPING_H
#define RNS_KEYCODE_MAPPING_H
#include <iostream>
typedef enum rnsKey{
    /*
     * RCU KEYS
     */
    RNS_KEY_Right,
    RNS_KEY_Left,
    RNS_KEY_Up,
    RNS_KEY_Down,
    RNS_KEY_Select,
    RNS_KEY_PowerOff,
    RNS_KEY_AudioMedia,
    RNS_KEY_Menu,
    RNS_KEY_AudioLowerVolume,
    RNS_KEY_AudioRaiseVolume,
    RNS_KEY_ChannelUp,
    RNS_KEY_ChannelDown,
    RNS_KEY_Help,
    RNS_KEY_Refresh,
    RNS_KEY_AudioStop,
    RNS_KEY_AudioPlay,
    RNS_KEY_AudioPause,
    RNS_KEY_Back,
    RNS_KEY_AudioNext,
    RNS_KEY_AudioRewind,
    RNS_KEY_AudioForward,
    RNS_KEY_AudioPrev,
    RNS_KEY_Green,
    RNS_KEY_Red,
    RNS_KEY_Blue,
    RNS_KEY_Yellow,
    RNS_KEY_1,
    RNS_KEY_2,
    RNS_KEY_3,
    RNS_KEY_4,
    RNS_KEY_5,
    RNS_KEY_6,
    RNS_KEY_7,
    RNS_KEY_8,
    RNS_KEY_9,
    RNS_KEY_0,
    RNS_KEY_TvRad,
    RNS_KEY_AudioRecord,
    RNS_KEY_Aud,
    RNS_KEY_Cancel,
    RNS_KEY_Mute,
    RNS_KEY_Guia,
    /*
     * KeyBoard Keys
     */
    /*Upper case Alphabets*/
    RNS_KEY_A,
    RNS_KEY_B,
    RNS_KEY_C,
    RNS_KEY_D,
    RNS_KEY_E,
    RNS_KEY_F,
    RNS_KEY_G,
    RNS_KEY_H,
    RNS_KEY_I,
    RNS_KEY_J,
    RNS_KEY_K,
    RNS_KEY_L,
    RNS_KEY_M,
    RNS_KEY_N,
    RNS_KEY_O,
    RNS_KEY_P,
    RNS_KEY_Q,
    RNS_KEY_R,
    RNS_KEY_S,
    RNS_KEY_T,
    RNS_KEY_U,
    RNS_KEY_V,
    RNS_KEY_W,
    RNS_KEY_X,
    RNS_KEY_Y,
    RNS_KEY_Z,
    /*Lower case Alphabets*/
    RNS_KEY_a,
    RNS_KEY_b,
    RNS_KEY_c,
    RNS_KEY_d,
    RNS_KEY_e,
    RNS_KEY_f,
    RNS_KEY_g,
    RNS_KEY_h,
    RNS_KEY_i,
    RNS_KEY_j,
    RNS_KEY_k,
    RNS_KEY_l,
    RNS_KEY_m,
    RNS_KEY_n,
    RNS_KEY_o,
    RNS_KEY_p,
    RNS_KEY_q,
    RNS_KEY_r,
    RNS_KEY_s,
    RNS_KEY_t,
    RNS_KEY_u,
    RNS_KEY_v,
    RNS_KEY_w,
    RNS_KEY_x,
    RNS_KEY_y,
    RNS_KEY_z,
    /*Modifer Keys chars*/
    RNS_KEY_CapsLock,
    RNS_KEY_AltL,
    RNS_KEY_AltR,
    RNS_KEY_ShiftL,
    RNS_KEY_ShiftR,
    RNS_KEY_ControlL,
    RNS_KEY_ControlR,
    /*Special char*/
    RNS_KEY_Tab,
    RNS_KEY_Backquote,
    //RNS_KEY_BackSpace,
    RNS_KEY_Tild,
    RNS_KEY_exclam,
    RNS_KEY_At,
    RNS_KEY_Hash,
    RNS_KEY_Dolar,
    RNS_KEY_Caret,
    RNS_KEY_Ampresend,
    RNS_KEY_Asterisk,
    RNS_KEY_LeftParaenthesis,
    RNS_KEY_RightParenthesis,
    RNS_KEY_Underscore,
    RNS_KEY_Delete,
    RNS_KEY_PageUp,
    RNS_KEY_PageDown,
    RNS_KEY_Shash,
    RNS_KEY_Period,
    RNS_KEY_Comma,
    RNS_KEY_Question,
    RNS_KEY_Quote,
    RNS_KEY_DoubleQuote,
    RNS_KEY_Semicolon,
    RNS_KEY_Colon,
    RNS_KEY_Pipe,
    RNS_KEY_BackSlash,
    RNS_KEY_OpenBace,
    RNS_KEY_CloseBrace,
    RNS_KEY_BracketLeft,
    RNS_KEY_BracketRight,
    RNS_KEY_Escape,
    RNS_KEY_Space,
    RNS_KEY_Home,
    RNS_KEY_EndKey,
    RNS_KEY_Insert,
    /*Arthematic */
    RNS_KEY_Minus,
    RNS_KEY_Equal,
    RNS_KEY_Percent,
    RNS_KEY_Pluse,
    RNS_KEY_Grater,
    RNS_KEY_Lesser,
    /*
     * Un mapped key
     */
    RNS_KEY_UnKnown,
    RNS_KEY_End
}rnsKey;

typedef enum rnsKeyAction{
    RNS_KEY_UnknownAction = -1,
    RNS_KEY_Press,
    RNS_KEY_Release
}rnsKeyAction;
static std::string RNSKeyMap[RNS_KEY_End]={
    "right",
    "left",
    "up",
    "down",
    "select",
    "powerOff",
    "audioMedia",
    "menu",
    "audioLowerVolume",
    "audioRaiseVolume",
    "channelUp",
    "channelDown",
    "help",
    "refresh",
    "stop",
    "play",
    "pause",
    "back",
    "next",
    "rewind",
    "fastForward",
    "previous",
    "green",
    "red",
    "blue",
    "yellow",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "tvRad",
    "audioRecord",
    "aud",
    "cancel",
    "mute",
    "guia",
    /*
     * KeyBoard Keys.
     */
    /* Upper case Alphabets*/
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    /* Lower case Alphabets*/
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z",
    /*Modfier Keys*/
    "CapsLock",
    "AltL",
    "AltR",
    "ShiftL",
    "ShiftR",
    "ControlL",
    "ControlR",
    /*Special chars*/
    "tab",
    "`",
    "~",
    "!",
    "@",
    "#",
    "$",
    "^",
    "&",
    "*",
    "(",
    ")",
    "_",
    "delete",
    "pageUp",
    "pageDown",
    "/",
    ".",
    ",",
    "?",
    "'",
    "\"",
    ";",
    ":",
    "|",
    "\\",
    "{",
    "}",
    "[",
    "]",
    "escape",
    " ",
    "Home",
    "End",
    "insert",
    /*
     * Arthematic Opps
     */
    "-",
    "=",
    "%",
    "+",
    ">",
    "<",

    "UnKnown"
};
#endif// __RNSKeyCodeMapping_h__
