#include <X11/Xutil.h>
#include "WindowX11.h"
using namespace std;
key  RnsShell::WindowX11::keyIdentifierForX11KeyCode(KeySym keycode){
    switch (keycode) {
    case XK_Left: return KEY_Left;
    case XK_Right: return KEY_Right;
    case XK_Up: return KEY_Up;
    case XK_Down: return KEY_Down;
    case XK_Return:
    case XK_Select: return KEY_Select;
    case XK_Menu: return KEY_Menu;
    case XK_Pause: return KEY_AudioPause;
    case XK_BackSpace: return KEY_Back;
    case XK_0: return KEY_0;
    case XK_1: return KEY_1;
    case XK_2: return KEY_2;
    case XK_3: return KEY_3;
    case XK_4: return KEY_4;
    case XK_5: return KEY_5;
    case XK_6: return KEY_6;
    case XK_7: return KEY_7;
    case XK_8: return KEY_8;
    case XK_9: return KEY_9;
    case XK_Cancel: return KEY_Cancel;
    /*
     * KeyBoard Keys.
     */
    /*Upper case Alphabets*/
    case XK_A: return KEY_A;
    case XK_B: return KEY_B;
    case XK_C: return KEY_C;
    case XK_D: return KEY_D;
    case XK_E: return KEY_E;
    case XK_F: return KEY_F;
    case XK_G: return KEY_G;
    case XK_H: return KEY_H;
    case XK_I: return KEY_I;
    case XK_J: return KEY_J;
    case XK_K: return KEY_K;
    case XK_L: return KEY_L;
    case XK_M: return KEY_M;
    case XK_N: return KEY_N;
    case XK_O: return KEY_O;
    case XK_P: return KEY_P;
    case XK_Q: return KEY_Q;
    case XK_R: return KEY_R;
    case XK_S: return KEY_S;
    case XK_T: return KEY_T;
    case XK_U: return KEY_U;
    case XK_V: return KEY_V;
    case XK_W: return KEY_W;
    case XK_X: return KEY_X;
    case XK_Y: return KEY_Y;
    case XK_Z: return KEY_Z;
    /*Lower case Alphabets*/
    case XK_a: return KEY_a;
    case XK_b: return KEY_b;
    case XK_c: return KEY_c;
    case XK_d: return KEY_d;
    case XK_e: return KEY_e;
    case XK_f: return KEY_f;
    case XK_g: return KEY_g;
    case XK_h: return KEY_h;
    case XK_i: return KEY_i;
    case XK_j: return KEY_j;
    case XK_k: return KEY_k;
    case XK_l: return KEY_l;
    case XK_m: return KEY_m;
    case XK_n: return KEY_n;
    case XK_o: return KEY_o;
    case XK_p: return KEY_p;
    case XK_q: return KEY_q;
    case XK_r: return KEY_r;
    case XK_s: return KEY_s;
    case XK_t: return KEY_t;
    case XK_u: return KEY_u;
    case XK_v: return KEY_v;
    case XK_w: return KEY_w;
    case XK_x: return KEY_x;
    case XK_y: return KEY_y;
    case XK_z: return KEY_z;
    /*Modifiers*/
    case XK_Caps_Lock: return KEY_Caps_Lock;
    case XK_Alt_L: return KEY_Alt_L;
    case XK_Alt_R: return KEY_Alt_R;
    case XK_Shift_L: return KEY_Shift_L;
    case XK_Shift_R: return KEY_Shift_R;
    case XK_Control_L: return KEY_Control_L;
    case XK_Control_R: return KEY_Control_R;
    /* Special char */
    case XK_Tab : return KEY_Tab;
    case XK_grave: return KEY_Grave;
    case XK_asciitilde: return KEY_Asciitilde;
    case XK_exclam: return KEY_Exclam;
    case XK_at: return KEY_At;
    case XK_numbersign: return KEY_Numbersign;
    case XK_dollar: return KEY_Dollar;
    case XK_asciicircum: return KEY_Asciicircum;
    case XK_ampersand: return KEY_Ampersand;
    case XK_asterisk: return KEY_Asterisk;
    case XK_parenleft: return KEY_ParenLeft;
    case XK_parenright: return KEY_ParenRight;
    case XK_underscore: return KEY_Underscore;
    case XK_Delete: return KEY_Delete;
    case XK_Page_Up: return KEY_Page_Up;
    case XK_Page_Down: return KEY_Page_Down;
    case XK_slash: return KEY_Shash;
    case XK_period: return KEY_Period;
    case XK_comma: return KEY_Comma;
    case XK_question: return KEY_Question;
    case XK_apostrophe: return KEY_Apostrophe;
    case XK_quotedbl: return KEY_Quotedbl;
    case XK_colon: return KEY_Colon;
    case XK_semicolon: return KEY_Semicolon;
    case XK_bar: return KEY_Bar;
    case XK_backslash : return KEY_BackSlash;
    case XK_braceleft: return KEY_BraceLeft;
    case XK_braceright: return KEY_BraceRight;
    case XK_bracketleft : return KEY_BracketLeft;
    case XK_bracketright: return KEY_BracketRight;
    case XK_Escape: return KEY_Escape;
    case XK_space: return KEY_Space;
    case XK_Home: return KEY_Home;
    case XK_End: return KEY_EndKey;
    case XK_Insert: return KEY_Insert;
    /*
     * Arithematic
     */
    case XK_minus: return KEY_Minus;
    case XK_equal: return KEY_Equal;
    case XK_percent: return KEY_Percent;
    case XK_plus: return KEY_Plus;
    case XK_greater: return KEY_Greater;
    case XK_less: return KEY_Less;

    default: return KEY_UnKnown;
    }
}

