#include <wpe/wpe.h>
#include "WindowLibWPE.h"
using namespace std;
key  RnsShell::WindowLibWPE::keyIdentifierForWPEKeyCode(int keyCode){
    switch (keyCode) {
    case WPE_KEY_Left: return KEY_Left;
    case WPE_KEY_Right: return KEY_Right;
    case WPE_KEY_Up: return KEY_Up;
    case WPE_KEY_Down: return KEY_Down;
    case WPE_KEY_Select:
    case WPE_KEY_ISO_Enter:
    case WPE_KEY_Return: return KEY_Select;
    case WPE_KEY_PowerOff: return KEY_PowerOff;
    case WPE_KEY_AudioMedia: return KEY_AudioMedia;
    case 0XF067:
    case WPE_KEY_Menu: return KEY_Menu;
    case 0xF04D:
    case WPE_KEY_AudioLowerVolume: return KEY_AudioLowerVolume;
    case 0xF04C:
    case WPE_KEY_AudioRaiseVolume: return KEY_AudioRaiseVolume;
    case 0XF046: return KEY_ChannelUp;
    case 0XF047: return KEY_ChannelDown;
    case 0XF014: return KEY_Help;
    case WPE_KEY_Refresh: return KEY_Refresh;
    case 0xF052:
    case WPE_KEY_AudioStop: return KEY_AudioStop;
    case 0XF051:
    case WPE_KEY_AudioPlay: return KEY_AudioPlay;
    case 0XFF13:
    case WPE_KEY_AudioPause: return KEY_AudioPause;
    case WPE_KEY_Back: return KEY_Back;
    case 0XF05C:
    case WPE_KEY_AudioNext: return KEY_AudioNext;
    case 0xF059:
    case WPE_KEY_AudioRewind: return KEY_AudioRewind;
    case 0xF05A:
    case WPE_KEY_AudioForward: return KEY_AudioForward;
    case 0XF05B:
    case WPE_KEY_AudioPrev: return KEY_AudioPrev;
    case 0XF043:
    case WPE_KEY_Green: return KEY_Green;
    case 0XF042:
    case WPE_KEY_Red: return KEY_Red;
    case 0XF045:
    case WPE_KEY_Blue: return KEY_Blue;
    case 0XF044:
    case WPE_KEY_Yellow: return KEY_Yellow;
    case WPE_KEY_1: return KEY_1;
    case WPE_KEY_2: return KEY_2;
    case WPE_KEY_3: return KEY_3;
    case WPE_KEY_4: return KEY_4;
    case WPE_KEY_5: return KEY_5;
    case WPE_KEY_6: return KEY_6;
    case WPE_KEY_7: return KEY_7;
    case WPE_KEY_8: return KEY_8;
    case WPE_KEY_9: return KEY_9;
    case WPE_KEY_0: return KEY_0;
    case 0xF02F: return KEY_TvRad;
    case 0xF037: return KEY_Aud;
    case 0XF056:
    case WPE_KEY_AudioRecord: return KEY_AudioRecord;
    case 0XF062:
    case WPE_KEY_Cancel: return KEY_Cancel;
    case 0XF04E:
    case WPE_KEY_AudioMute: return KEY_Mute;
    case 0XF01B: return KEY_Guia;
    /*Upper Case Alpha */
    case WPE_KEY_A: return KEY_A;
    case WPE_KEY_B: return KEY_B;
    case WPE_KEY_C: return KEY_C;
    case WPE_KEY_D: return KEY_D;
    case WPE_KEY_E: return KEY_E;
    case WPE_KEY_F: return KEY_F;
    case WPE_KEY_G: return KEY_G;
    case WPE_KEY_H: return KEY_H;
    case WPE_KEY_I: return KEY_I;
    case WPE_KEY_J: return KEY_J;
    case WPE_KEY_K: return KEY_K;
    case WPE_KEY_L: return KEY_L;
    case WPE_KEY_M: return KEY_M;
    case WPE_KEY_N: return KEY_N;
    case WPE_KEY_O: return KEY_O;
    case WPE_KEY_P: return KEY_P;
    case WPE_KEY_Q: return KEY_Q;
    case WPE_KEY_R: return KEY_R;
    case WPE_KEY_S: return KEY_S;
    case WPE_KEY_T: return KEY_T;
    case WPE_KEY_U: return KEY_U;
    case WPE_KEY_V: return KEY_V;
    case WPE_KEY_W: return KEY_W;
    case WPE_KEY_X: return KEY_X;
    case WPE_KEY_Y: return KEY_Y;
    case WPE_KEY_Z: return KEY_Z;
    /*Lower Case Alpha*/
    case WPE_KEY_a: return KEY_a;
    case WPE_KEY_b: return KEY_b;
    case WPE_KEY_c: return KEY_c;
    case WPE_KEY_d: return KEY_d;
    case WPE_KEY_e: return KEY_e;
    case WPE_KEY_f: return KEY_f;
    case WPE_KEY_g: return KEY_g;
    case WPE_KEY_h: return KEY_h;
    case WPE_KEY_i: return KEY_i;
    case WPE_KEY_j: return KEY_j;
    case WPE_KEY_k: return KEY_k;
    case WPE_KEY_l: return KEY_l;
    case WPE_KEY_m: return KEY_m;
    case WPE_KEY_n: return KEY_n;
    case WPE_KEY_o: return KEY_o;
    case WPE_KEY_p: return KEY_p;
    case WPE_KEY_q: return KEY_q;
    case WPE_KEY_r: return KEY_r;
    case WPE_KEY_s: return KEY_s;
    case WPE_KEY_t: return KEY_t;
    case WPE_KEY_u: return KEY_u;
    case WPE_KEY_v: return KEY_v;
    case WPE_KEY_w: return KEY_w;
    case WPE_KEY_x: return KEY_x;
    case WPE_KEY_y: return KEY_y;
    case WPE_KEY_z: return KEY_z;
    /*Modifier keys */
    case WPE_KEY_Caps_Lock : return KEY_Caps_Lock;
    case WPE_KEY_Alt_L: return KEY_Alt_L;
    case WPE_KEY_Alt_R: return KEY_Alt_R;
    case WPE_KEY_Shift_L: return KEY_Shift_L;
    case WPE_KEY_Shift_R: return KEY_Shift_R;
    case WPE_KEY_Control_L: return KEY_Control_L;
    case WPE_KEY_Control_R: return KEY_Control_R;
    /*special case */
    case WPE_KEY_Tab: return KEY_Tab;
    case WPE_KEY_grave: return KEY_Grave;
    case WPE_KEY_BackSpace: return KEY_Back;
    case WPE_KEY_asciitilde: return KEY_Asciitilde;
    case WPE_KEY_exclam: return KEY_Exclam;
    case WPE_KEY_at : return KEY_At;
    case WPE_KEY_numbersign: return KEY_Numbersign;
    case WPE_KEY_dollar: return KEY_Dollar;
    case WPE_KEY_asciicircum: return KEY_Asciicircum;
    case WPE_KEY_ampersand: return KEY_Ampersand;
    case WPE_KEY_asterisk: return KEY_Asterisk;
    case WPE_KEY_braceleft: return KEY_BraceLeft;
    case WPE_KEY_braceright: return KEY_BraceRight;
    case WPE_KEY_underscore: return KEY_Underscore;
    case WPE_KEY_Delete: return KEY_Delete;
    case WPE_KEY_Page_Up: return KEY_Page_Up;
    case WPE_KEY_Page_Down: return KEY_Page_Down;
    case WPE_KEY_slash: return KEY_Shash;
    case WPE_KEY_period: return KEY_Period;
    case WPE_KEY_comma: return KEY_Comma;
    case WPE_KEY_question: return KEY_Question;
    case WPE_KEY_apostrophe: return KEY_Apostrophe;
    case WPE_KEY_quotedbl: return KEY_Quotedbl;
    case WPE_KEY_semicolon: return KEY_Semicolon;
    case WPE_KEY_colon: return KEY_Colon;
    case WPE_KEY_bar: return KEY_Bar;
    case WPE_KEY_backslash: return KEY_BackSlash;
    case WPE_KEY_parenleft: return   KEY_ParenLeft;
    case WPE_KEY_parenright: return KEY_ParenRight;
    case WPE_KEY_bracketleft: return KEY_BracketLeft;
    case WPE_KEY_bracketright: return KEY_BracketRight;
    case WPE_KEY_Escape: return KEY_Escape;
    case WPE_KEY_space: return KEY_Space;
    case WPE_KEY_Home: return KEY_Home;
    case WPE_KEY_End : return KEY_EndKey;
    case WPE_KEY_Insert: return KEY_Insert;
    /*Arthimatic*/
    case WPE_KEY_minus: return KEY_Minus;
    case WPE_KEY_equal: return KEY_Equal;
    case WPE_KEY_percent: return KEY_Percent;
    case WPE_KEY_plus: return KEY_Plus;
    case WPE_KEY_greater: return KEY_Greater;
    case WPE_KEY_less : return KEY_Less;
    /*UnKnownKey*/
    default: return KEY_UnKnown;
    }
}
