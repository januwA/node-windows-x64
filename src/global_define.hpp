 #pragma once
#include <napi.h>
#include "_napi_macro.h"
#include <Windows.h>

Napi::Value globalDefine(const Napi::CallbackInfo &info)
{
  nm_init;
  Napi::Object g;
  if (info.Length() && nmi_is_obj(0))
    g = nmi_obj(0);
  else
    g = env.Global();

  
  /*
   * Window Messages
   */
  g.Set("WM_NULL", 0x0000);g.Set("WM_CREATE", 0x0001);g.Set("WM_DESTROY", 0x0002);g.Set("WM_MOVE", 0x0003);g.Set("WM_SIZE", 0x0005);g.Set("WM_ACTIVATE", 0x0006);g.Set("WM_SETFOCUS", 0x0007);g.Set("WM_KILLFOCUS", 0x0008);g.Set("WM_ENABLE", 0x000A);g.Set("WM_SETREDRAW", 0x000B);g.Set("WM_SETTEXT", 0x000C);g.Set("WM_GETTEXT", 0x000D);g.Set("WM_GETTEXTLENGTH", 0x000E);g.Set("WM_PAINT", 0x000F);g.Set("WM_CLOSE", 0x0010);g.Set("WM_QUERYENDSESSION", 0x0011);g.Set("WM_QUERYOPEN", 0x0013);g.Set("WM_ENDSESSION", 0x0016);g.Set("WM_QUIT", 0x0012);g.Set("WM_ERASEBKGND", 0x0014);g.Set("WM_SYSCOLORCHANGE", 0x0015);g.Set("WM_SHOWWINDOW", 0x0018);g.Set("WM_WININICHANGE", 0x001A);g.Set("WM_SETTINGCHANGE", WM_WININICHANGE);g.Set("WM_DEVMODECHANGE", 0x001B);g.Set("WM_ACTIVATEAPP", 0x001C);g.Set("WM_FONTCHANGE", 0x001D);g.Set("WM_TIMECHANGE", 0x001E);g.Set("WM_CANCELMODE", 0x001F);g.Set("WM_SETCURSOR", 0x0020);g.Set("WM_MOUSEACTIVATE", 0x0021);g.Set("WM_CHILDACTIVATE", 0x0022);g.Set("WM_QUEUESYNC", 0x0023);g.Set("WM_GETMINMAXINFO", 0x0024);g.Set("WM_PAINTICON", 0x0026);g.Set("WM_ICONERASEBKGND", 0x0027);g.Set("WM_NEXTDLGCTL", 0x0028);g.Set("WM_SPOOLERSTATUS", 0x002A);g.Set("WM_DRAWITEM", 0x002B);g.Set("WM_MEASUREITEM", 0x002C);g.Set("WM_DELETEITEM", 0x002D);g.Set("WM_VKEYTOITEM", 0x002E);g.Set("WM_CHARTOITEM", 0x002F);g.Set("WM_SETFONT", 0x0030);g.Set("WM_GETFONT", 0x0031);g.Set("WM_SETHOTKEY", 0x0032);g.Set("WM_GETHOTKEY", 0x0033);g.Set("WM_QUERYDRAGICON", 0x0037);g.Set("WM_COMPAREITEM", 0x0039);g.Set("WM_GETOBJECT", 0x003D);g.Set("WM_COMPACTING", 0x0041);g.Set("WM_COMMNOTIFY", 0x0044);g.Set("WM_WINDOWPOSCHANGING", 0x0046);g.Set("WM_WINDOWPOSCHANGED", 0x0047);g.Set("WM_POWER", 0x0048);g.Set("WM_COPYDATA", 0x004A);g.Set("WM_CANCELJOURNAL", 0x004B);g.Set("WM_NOTIFY", 0x004E);g.Set("WM_INPUTLANGCHANGEREQUEST", 0x0050);g.Set("WM_INPUTLANGCHANGE", 0x0051);g.Set("WM_TCARD", 0x0052);g.Set("WM_HELP", 0x0053);g.Set("WM_USERCHANGED", 0x0054);g.Set("WM_NOTIFYFORMAT", 0x0055);g.Set("WM_CONTEXTMENU", 0x007B);g.Set("WM_STYLECHANGING", 0x007C);g.Set("WM_STYLECHANGED", 0x007D);g.Set("WM_DISPLAYCHANGE", 0x007E);g.Set("WM_GETICON", 0x007F);g.Set("WM_SETICON", 0x0080);g.Set("WM_NCCREATE", 0x0081);g.Set("WM_NCDESTROY", 0x0082);g.Set("WM_NCCALCSIZE", 0x0083);g.Set("WM_NCHITTEST", 0x0084);g.Set("WM_NCPAINT", 0x0085);g.Set("WM_NCACTIVATE", 0x0086);g.Set("WM_GETDLGCODE", 0x0087);g.Set("WM_SYNCPAINT", 0x0088);g.Set("WM_NCMOUSEMOVE", 0x00A0);g.Set("WM_NCLBUTTONDOWN", 0x00A1);g.Set("WM_NCLBUTTONUP", 0x00A2);g.Set("WM_NCLBUTTONDBLCLK", 0x00A3);g.Set("WM_NCRBUTTONDOWN", 0x00A4);g.Set("WM_NCRBUTTONUP", 0x00A5);g.Set("WM_NCRBUTTONDBLCLK", 0x00A6);g.Set("WM_NCMBUTTONDOWN", 0x00A7);g.Set("WM_NCMBUTTONUP", 0x00A8);g.Set("WM_NCMBUTTONDBLCLK", 0x00A9);g.Set("WM_NCXBUTTONDOWN", 0x00AB);g.Set("WM_NCXBUTTONUP", 0x00AC);g.Set("WM_NCXBUTTONDBLCLK", 0x00AD);g.Set("WM_INPUT_DEVICE_CHANGE", 0x00FE);g.Set("WM_INPUT", 0x00FF);g.Set("WM_KEYFIRST", 0x0100);g.Set("WM_KEYDOWN", 0x0100);g.Set("WM_KEYUP", 0x0101);g.Set("WM_CHAR", 0x0102);g.Set("WM_DEADCHAR", 0x0103);g.Set("WM_SYSKEYDOWN", 0x0104);g.Set("WM_SYSKEYUP", 0x0105);g.Set("WM_SYSCHAR", 0x0106);g.Set("WM_SYSDEADCHAR", 0x0107);g.Set("WM_UNICHAR", 0x0109);g.Set("WM_KEYLAST", 0x0109);g.Set("WM_IME_STARTCOMPOSITION", 0x010D);g.Set("WM_IME_ENDCOMPOSITION", 0x010E);g.Set("WM_IME_COMPOSITION", 0x010F);g.Set("WM_IME_KEYLAST", 0x010F);g.Set("WM_INITDIALOG", 0x0110);g.Set("WM_COMMAND", 0x0111);g.Set("WM_SYSCOMMAND", 0x0112);g.Set("WM_TIMER", 0x0113);g.Set("WM_HSCROLL", 0x0114);g.Set("WM_VSCROLL", 0x0115);g.Set("WM_INITMENU", 0x0116);g.Set("WM_INITMENUPOPUP", 0x0117);g.Set("WM_GESTURE", 0x0119);g.Set("WM_GESTURENOTIFY", 0x011A);g.Set("WM_MENUSELECT", 0x011F);g.Set("WM_MENUCHAR", 0x0120);g.Set("WM_ENTERIDLE", 0x0121);g.Set("WM_MENURBUTTONUP", 0x0122);g.Set("WM_MENUDRAG", 0x0123);g.Set("WM_MENUGETOBJECT", 0x0124);g.Set("WM_UNINITMENUPOPUP", 0x0125);g.Set("WM_MENUCOMMAND", 0x0126);g.Set("WM_CHANGEUISTATE", 0x0127);g.Set("WM_UPDATEUISTATE", 0x0128);g.Set("WM_QUERYUISTATE", 0x0129);g.Set("WM_CTLCOLORMSGBOX", 0x0132);g.Set("WM_CTLCOLOREDIT", 0x0133);g.Set("WM_CTLCOLORLISTBOX", 0x0134);g.Set("WM_CTLCOLORBTN", 0x0135);g.Set("WM_CTLCOLORDLG", 0x0136);g.Set("WM_CTLCOLORSCROLLBAR", 0x0137);g.Set("WM_CTLCOLORSTATIC", 0x0138);g.Set("WM_MOUSEFIRST", 0x0200);g.Set("WM_MOUSEMOVE", 0x0200);g.Set("WM_LBUTTONDOWN", 0x0201);g.Set("WM_LBUTTONUP", 0x0202);g.Set("WM_LBUTTONDBLCLK", 0x0203);g.Set("WM_RBUTTONDOWN", 0x0204);g.Set("WM_RBUTTONUP", 0x0205);g.Set("WM_RBUTTONDBLCLK", 0x0206);g.Set("WM_MBUTTONDOWN", 0x0207);g.Set("WM_MBUTTONUP", 0x0208);g.Set("WM_MBUTTONDBLCLK", 0x0209);g.Set("WM_MOUSEWHEEL", 0x020A);g.Set("WM_XBUTTONDOWN", 0x020B);g.Set("WM_XBUTTONUP", 0x020C);g.Set("WM_XBUTTONDBLCLK", 0x020D);g.Set("WM_MOUSEHWHEEL", 0x020E);g.Set("WM_MOUSELAST", 0x020E);g.Set("WM_PARENTNOTIFY", 0x0210);g.Set("WM_ENTERMENULOOP", 0x0211);g.Set("WM_EXITMENULOOP", 0x0212);g.Set("WM_NEXTMENU", 0x0213);g.Set("WM_SIZING", 0x0214);g.Set("WM_CAPTURECHANGED", 0x0215);g.Set("WM_MOVING", 0x0216);g.Set("WM_POWERBROADCAST", 0x0218);g.Set("WM_DEVICECHANGE", 0x0219);g.Set("WM_MDICREATE", 0x0220);g.Set("WM_MDIDESTROY", 0x0221);g.Set("WM_MDIACTIVATE", 0x0222);g.Set("WM_MDIRESTORE", 0x0223);g.Set("WM_MDINEXT", 0x0224);g.Set("WM_MDIMAXIMIZE", 0x0225);g.Set("WM_MDITILE", 0x0226);g.Set("WM_MDICASCADE", 0x0227);g.Set("WM_MDIICONARRANGE", 0x0228);g.Set("WM_MDIGETACTIVE", 0x0229);g.Set("WM_MDISETMENU", 0x0230);g.Set("WM_ENTERSIZEMOVE", 0x0231);g.Set("WM_EXITSIZEMOVE", 0x0232);g.Set("WM_DROPFILES", 0x0233);g.Set("WM_MDIREFRESHMENU", 0x0234);g.Set("WM_POINTERDEVICECHANGE", 0x238);g.Set("WM_POINTERDEVICEINRANGE", 0x239);g.Set("WM_POINTERDEVICEOUTOFRANGE", 0x23A);g.Set("WM_TOUCH", 0x0240);g.Set("WM_NCPOINTERUPDATE", 0x0241);g.Set("WM_NCPOINTERDOWN", 0x0242);g.Set("WM_NCPOINTERUP", 0x0243);g.Set("WM_POINTERUPDATE", 0x0245);g.Set("WM_POINTERDOWN", 0x0246);g.Set("WM_POINTERUP", 0x0247);g.Set("WM_POINTERENTER", 0x0249);g.Set("WM_POINTERLEAVE", 0x024A);g.Set("WM_POINTERACTIVATE", 0x024B);g.Set("WM_POINTERCAPTURECHANGED", 0x024C);g.Set("WM_TOUCHHITTESTING", 0x024D);g.Set("WM_POINTERWHEEL", 0x024E);g.Set("WM_POINTERHWHEEL", 0x024F);g.Set("WM_POINTERROUTEDTO", 0x0251);g.Set("WM_POINTERROUTEDAWAY", 0x0252);g.Set("WM_POINTERROUTEDRELEASED", 0x0253);g.Set("WM_IME_SETCONTEXT", 0x0281);g.Set("WM_IME_NOTIFY", 0x0282);g.Set("WM_IME_CONTROL", 0x0283);g.Set("WM_IME_COMPOSITIONFULL", 0x0284);g.Set("WM_IME_SELECT", 0x0285);g.Set("WM_IME_CHAR", 0x0286);g.Set("WM_IME_REQUEST", 0x0288);g.Set("WM_IME_KEYDOWN", 0x0290);g.Set("WM_IME_KEYUP", 0x0291);g.Set("WM_MOUSEHOVER", 0x02A1);g.Set("WM_MOUSELEAVE", 0x02A3);g.Set("WM_NCMOUSEHOVER", 0x02A0);g.Set("WM_NCMOUSELEAVE", 0x02A2);g.Set("WM_WTSSESSION_CHANGE", 0x02B1);g.Set("WM_TABLET_FIRST", 0x02c0);g.Set("WM_TABLET_LAST", 0x02df);g.Set("WM_DPICHANGED", 0x02E0);g.Set("WM_DPICHANGED_BEFOREPARENT", 0x02E2);g.Set("WM_DPICHANGED_AFTERPARENT", 0x02E3);g.Set("WM_GETDPISCALEDSIZE", 0x02E4);g.Set("WM_CUT", 0x0300);g.Set("WM_COPY", 0x0301);g.Set("WM_PASTE", 0x0302);g.Set("WM_CLEAR", 0x0303);g.Set("WM_UNDO", 0x0304);g.Set("WM_RENDERFORMAT", 0x0305);g.Set("WM_RENDERALLFORMATS", 0x0306);g.Set("WM_DESTROYCLIPBOARD", 0x0307);g.Set("WM_DRAWCLIPBOARD", 0x0308);g.Set("WM_PAINTCLIPBOARD", 0x0309);g.Set("WM_VSCROLLCLIPBOARD", 0x030A);g.Set("WM_SIZECLIPBOARD", 0x030B);g.Set("WM_ASKCBFORMATNAME", 0x030C);g.Set("WM_CHANGECBCHAIN", 0x030D);g.Set("WM_HSCROLLCLIPBOARD", 0x030E);g.Set("WM_QUERYNEWPALETTE", 0x030F);g.Set("WM_PALETTEISCHANGING", 0x0310);g.Set("WM_PALETTECHANGED", 0x0311);g.Set("WM_HOTKEY", 0x0312);g.Set("WM_PRINT", 0x0317);g.Set("WM_PRINTCLIENT", 0x0318);g.Set("WM_APPCOMMAND", 0x0319);g.Set("WM_THEMECHANGED", 0x031A);g.Set("WM_CLIPBOARDUPDATE", 0x031D);g.Set("WM_DWMCOMPOSITIONCHANGED", 0x031E);g.Set("WM_DWMNCRENDERINGCHANGED", 0x031F);g.Set("WM_DWMCOLORIZATIONCOLORCHANGED", 0x0320);g.Set("WM_DWMWINDOWMAXIMIZEDCHANGE", 0x0321);g.Set("WM_DWMSENDICONICTHUMBNAIL", 0x0323);g.Set("WM_DWMSENDICONICLIVEPREVIEWBITMAP", 0x0326);g.Set("WM_GETTITLEBARINFOEX", 0x033F);g.Set("WM_HANDHELDFIRST", 0x0358);g.Set("WM_HANDHELDLAST", 0x035F);g.Set("WM_AFXFIRST", 0x0360);g.Set("WM_AFXLAST", 0x037F);g.Set("WM_PENWINFIRST", 0x0380);g.Set("WM_PENWINLAST", 0x038F);g.Set("WM_APP", 0x8000);g.Set("WM_USER", 0x0400);

  /*
   * Window Styles
   */
  g.Set("WS_OVERLAPPED", 0x00000000L);g.Set("WS_POPUP", 0x80000000L);g.Set("WS_CHILD", 0x40000000L);g.Set("WS_MINIMIZE", 0x20000000L);g.Set("WS_VISIBLE", 0x10000000L);g.Set("WS_DISABLED", 0x08000000L);g.Set("WS_CLIPSIBLINGS", 0x04000000L);g.Set("WS_CLIPCHILDREN", 0x02000000L);g.Set("WS_MAXIMIZE", 0x01000000L);g.Set("WS_CAPTION", 0x00C00000L);g.Set("WS_BORDER", 0x00800000L);g.Set("WS_DLGFRAME", 0x00400000L);g.Set("WS_VSCROLL", 0x00200000L);g.Set("WS_HSCROLL", 0x00100000L);g.Set("WS_SYSMENU", 0x00080000L);g.Set("WS_THICKFRAME", 0x00040000L);g.Set("WS_GROUP", 0x00020000L);g.Set("WS_TABSTOP", 0x00010000L);g.Set("WS_MINIMIZEBOX", 0x00020000L);g.Set("WS_MAXIMIZEBOX", 0x00010000L);g.Set("WS_TILED", WS_OVERLAPPED);g.Set("WS_ICONIC", WS_MINIMIZE);g.Set("WS_SIZEBOX", WS_THICKFRAME);g.Set("WS_TILEDWINDOW", WS_OVERLAPPEDWINDOW);g.Set("WS_OVERLAPPEDWINDOW", (WS_OVERLAPPED     | \
                             WS_CAPTION        | \
                             WS_SYSMENU        | \
                             WS_THICKFRAME     | \
                             WS_MINIMIZEBOX    | \
                             WS_MAXIMIZEBOX));g.Set("WS_POPUPWINDOW", (WS_POPUP          | \
                             WS_BORDER         | \
                             WS_SYSMENU));g.Set("WS_CHILDWINDOW", (WS_CHILD));g.Set("WS_EX_DLGMODALFRAME", 0x00000001L);g.Set("WS_EX_NOPARENTNOTIFY", 0x00000004L);g.Set("WS_EX_TOPMOST", 0x00000008L);g.Set("WS_EX_ACCEPTFILES", 0x00000010L);g.Set("WS_EX_TRANSPARENT", 0x00000020L);g.Set("WS_EX_MDICHILD", 0x00000040L);g.Set("WS_EX_TOOLWINDOW", 0x00000080L);g.Set("WS_EX_WINDOWEDGE", 0x00000100L);g.Set("WS_EX_CLIENTEDGE", 0x00000200L);g.Set("WS_EX_CONTEXTHELP", 0x00000400L);g.Set("WS_EX_RIGHT", 0x00001000L);g.Set("WS_EX_LEFT", 0x00000000L);g.Set("WS_EX_RTLREADING", 0x00002000L);g.Set("WS_EX_LTRREADING", 0x00000000L);g.Set("WS_EX_LEFTSCROLLBAR", 0x00004000L);g.Set("WS_EX_RIGHTSCROLLBAR", 0x00000000L);g.Set("WS_EX_CONTROLPARENT", 0x00010000L);g.Set("WS_EX_STATICEDGE", 0x00020000L);g.Set("WS_EX_APPWINDOW", 0x00040000L);g.Set("WS_EX_OVERLAPPEDWINDOW", (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE));g.Set("WS_EX_PALETTEWINDOW", (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST));g.Set("WS_EX_LAYERED", 0x00080000);g.Set("WS_EX_NOINHERITLAYOUT", 0x00100000L);g.Set("WS_EX_NOREDIRECTIONBITMAP", 0x00200000L);g.Set("WS_EX_LAYOUTRTL", 0x00400000L);g.Set("WS_EX_COMPOSITED", 0x02000000L);g.Set("WS_EX_NOACTIVATE", 0x08000000L);g.Set("WS_ACTIVECAPTION", 0x0001);

  /*
   * Class styles
   */
  g.Set("CS_VREDRAW", 0x0001);g.Set("CS_HREDRAW", 0x0002);g.Set("CS_DBLCLKS", 0x0008);g.Set("CS_OWNDC", 0x0020);g.Set("CS_CLASSDC", 0x0040);g.Set("CS_PARENTDC", 0x0080);g.Set("CS_NOCLOSE", 0x0200);g.Set("CS_SAVEBITS", 0x0800);g.Set("CS_BYTEALIGNCLIENT", 0x1000);g.Set("CS_BYTEALIGNWINDOW", 0x2000);g.Set("CS_GLOBALCLASS", 0x4000);g.Set("CS_IME", 0x00010000);g.Set("CS_DROPSHADOW", 0x00020000);

  /*
   * Button Control Styles
   */
  g.Set("BS_PUSHBUTTON", 0x00000000L);g.Set("BS_DEFPUSHBUTTON", 0x00000001L);g.Set("BS_CHECKBOX", 0x00000002L);g.Set("BS_AUTOCHECKBOX", 0x00000003L);g.Set("BS_RADIOBUTTON", 0x00000004L);g.Set("BS_3STATE", 0x00000005L);g.Set("BS_AUTO3STATE", 0x00000006L);g.Set("BS_GROUPBOX", 0x00000007L);g.Set("BS_USERBUTTON", 0x00000008L);g.Set("BS_AUTORADIOBUTTON", 0x00000009L);g.Set("BS_PUSHBOX", 0x0000000AL);g.Set("BS_OWNERDRAW", 0x0000000BL);g.Set("BS_TYPEMASK", 0x0000000FL);g.Set("BS_LEFTTEXT", 0x00000020L);g.Set("BS_TEXT", 0x00000000L);g.Set("BS_ICON", 0x00000040L);g.Set("BS_BITMAP", 0x00000080L);g.Set("BS_LEFT", 0x00000100L);g.Set("BS_RIGHT", 0x00000200L);g.Set("BS_CENTER", 0x00000300L);g.Set("BS_TOP", 0x00000400L);g.Set("BS_BOTTOM", 0x00000800L);g.Set("BS_VCENTER", 0x00000C00L);g.Set("BS_PUSHLIKE", 0x00001000L);g.Set("BS_MULTILINE", 0x00002000L);g.Set("BS_NOTIFY", 0x00004000L);g.Set("BS_FLAT", 0x00008000L);g.Set("BS_RIGHTBUTTON", BS_LEFTTEXT);

  /*
   * Button Control Messages
   */
  g.Set("BM_GETCHECK", 0x00F0);g.Set("BM_SETCHECK", 0x00F1);g.Set("BM_GETSTATE", 0x00F2);g.Set("BM_SETSTATE", 0x00F3);g.Set("BM_SETSTYLE", 0x00F4);g.Set("BM_CLICK", 0x00F5);g.Set("BM_GETIMAGE", 0x00F6);g.Set("BM_SETIMAGE", 0x00F7);g.Set("BM_SETDONTCLICK", 0x00F8);

  /*
   * Button State
   */
  g.Set("BST_UNCHECKED", 0x0000);g.Set("BST_CHECKED", 0x0001);g.Set("BST_INDETERMINATE", 0x0002);g.Set("BST_PUSHED", 0x0004);g.Set("BST_FOCUS", 0x0008);

  /*
   * Button Notification Codes
   */
  g.Set("BN_CLICKED", 0);g.Set("BN_PAINT", 1);g.Set("BN_HILITE", 2);g.Set("BN_UNHILITE", 3);g.Set("BN_DISABLE", 4);g.Set("BN_DOUBLECLICKED", 5);g.Set("BN_PUSHED", BN_HILITE);g.Set("BN_UNPUSHED", BN_UNHILITE);g.Set("BN_DBLCLK", BN_DOUBLECLICKED);g.Set("BN_SETFOCUS", 6);g.Set("BN_KILLFOCUS", 7);

  /*
   * Combo Box styles
   */
  g.Set("CBS_SIMPLE", 0x0001L);g.Set("CBS_DROPDOWN", 0x0002L);g.Set("CBS_DROPDOWNLIST", 0x0003L);g.Set("CBS_OWNERDRAWFIXED", 0x0010L);g.Set("CBS_OWNERDRAWVARIABLE", 0x0020L);g.Set("CBS_AUTOHSCROLL", 0x0040L);g.Set("CBS_OEMCONVERT", 0x0080L);g.Set("CBS_SORT", 0x0100L);g.Set("CBS_HASSTRINGS", 0x0200L);g.Set("CBS_NOINTEGRALHEIGHT", 0x0400L);g.Set("CBS_DISABLENOSCROLL", 0x0800L);g.Set("CBS_UPPERCASE", 0x2000L);g.Set("CBS_LOWERCASE", 0x4000L);

  /*
   * Combo Box messages
   */
  g.Set("CB_OKAY", 0);g.Set("CB_ERR", (-1));g.Set("CB_ERRSPACE", (-2));g.Set("CB_GETEDITSEL", 0x0140);g.Set("CB_LIMITTEXT", 0x0141);g.Set("CB_SETEDITSEL", 0x0142);g.Set("CB_ADDSTRING", 0x0143);g.Set("CB_DELETESTRING", 0x0144);g.Set("CB_DIR", 0x0145);g.Set("CB_GETCOUNT", 0x0146);g.Set("CB_GETCURSEL", 0x0147);g.Set("CB_GETLBTEXT", 0x0148);g.Set("CB_GETLBTEXTLEN", 0x0149);g.Set("CB_INSERTSTRING", 0x014A);g.Set("CB_RESETCONTENT", 0x014B);g.Set("CB_FINDSTRING", 0x014C);g.Set("CB_SELECTSTRING", 0x014D);g.Set("CB_SETCURSEL", 0x014E);g.Set("CB_SHOWDROPDOWN", 0x014F);g.Set("CB_GETITEMDATA", 0x0150);g.Set("CB_SETITEMDATA", 0x0151);g.Set("CB_GETDROPPEDCONTROLRECT", 0x0152);g.Set("CB_SETITEMHEIGHT", 0x0153);g.Set("CB_GETITEMHEIGHT", 0x0154);g.Set("CB_SETEXTENDEDUI", 0x0155);g.Set("CB_GETEXTENDEDUI", 0x0156);g.Set("CB_GETDROPPEDSTATE", 0x0157);g.Set("CB_FINDSTRINGEXACT", 0x0158);g.Set("CB_SETLOCALE", 0x0159);g.Set("CB_GETLOCALE", 0x015A);g.Set("CB_GETTOPINDEX", 0x015b);g.Set("CB_SETTOPINDEX", 0x015c);g.Set("CB_GETHORIZONTALEXTENT", 0x015d);g.Set("CB_SETHORIZONTALEXTENT", 0x015e);g.Set("CB_GETDROPPEDWIDTH", 0x015f);g.Set("CB_SETDROPPEDWIDTH", 0x0160);g.Set("CB_INITSTORAGE", 0x0161);g.Set("CB_MULTIPLEADDSTRING", 0x0163);g.Set("CB_GETCOMBOBOXINFO", 0x0164);g.Set("CB_MSGMAX", 0x0165);

  /*
   * Combo Box Notification Codes
   */
  g.Set("CBN_ERRSPACE", (-1));g.Set("CBN_SELCHANGE", 1);g.Set("CBN_DBLCLK", 2);g.Set("CBN_SETFOCUS", 3);g.Set("CBN_KILLFOCUS", 4);g.Set("CBN_EDITCHANGE", 5);g.Set("CBN_EDITUPDATE", 6);g.Set("CBN_DROPDOWN", 7);g.Set("CBN_CLOSEUP", 8);g.Set("CBN_SELENDOK", 9);g.Set("CBN_SELENDCANCEL", 10);

  /*
   * Listbox Styles
   */
  g.Set("ES_LEFT", 0x0000L);g.Set("ES_CENTER", 0x0001L);g.Set("ES_RIGHT", 0x0002L);g.Set("ES_MULTILINE", 0x0004L);g.Set("ES_UPPERCASE", 0x0008L);g.Set("ES_LOWERCASE", 0x0010L);g.Set("ES_PASSWORD", 0x0020L);g.Set("ES_AUTOVSCROLL", 0x0040L);g.Set("ES_AUTOHSCROLL", 0x0080L);g.Set("ES_NOHIDESEL", 0x0100L);g.Set("ES_OEMCONVERT", 0x0400L);g.Set("ES_READONLY", 0x0800L);g.Set("ES_WANTRETURN", 0x1000L);g.Set("ES_NUMBER", 0x2000L);

  /*
   * Listbox messages
   */
  g.Set("LB_CTLCODE", 0L);g.Set("LB_OKAY", 0);g.Set("LB_ERR", (-1));g.Set("LB_ERRSPACE", (-2));g.Set("LB_ADDSTRING", 0x0180);g.Set("LB_INSERTSTRING", 0x0181);g.Set("LB_DELETESTRING", 0x0182);g.Set("LB_SELITEMRANGEEX", 0x0183);g.Set("LB_RESETCONTENT", 0x0184);g.Set("LB_SETSEL", 0x0185);g.Set("LB_SETCURSEL", 0x0186);g.Set("LB_GETSEL", 0x0187);g.Set("LB_GETCURSEL", 0x0188);g.Set("LB_GETTEXT", 0x0189);g.Set("LB_GETTEXTLEN", 0x018A);g.Set("LB_GETCOUNT", 0x018B);g.Set("LB_SELECTSTRING", 0x018C);g.Set("LB_DIR", 0x018D);g.Set("LB_GETTOPINDEX", 0x018E);g.Set("LB_FINDSTRING", 0x018F);g.Set("LB_GETSELCOUNT", 0x0190);g.Set("LB_GETSELITEMS", 0x0191);g.Set("LB_SETTABSTOPS", 0x0192);g.Set("LB_GETHORIZONTALEXTENT", 0x0193);g.Set("LB_SETHORIZONTALEXTENT", 0x0194);g.Set("LB_SETCOLUMNWIDTH", 0x0195);g.Set("LB_ADDFILE", 0x0196);g.Set("LB_SETTOPINDEX", 0x0197);g.Set("LB_GETITEMRECT", 0x0198);g.Set("LB_GETITEMDATA", 0x0199);g.Set("LB_SETITEMDATA", 0x019A);g.Set("LB_SELITEMRANGE", 0x019B);g.Set("LB_SETANCHORINDEX", 0x019C);g.Set("LB_GETANCHORINDEX", 0x019D);g.Set("LB_SETCARETINDEX", 0x019E);g.Set("LB_GETCARETINDEX", 0x019F);g.Set("LB_SETITEMHEIGHT", 0x01A0);g.Set("LB_GETITEMHEIGHT", 0x01A1);g.Set("LB_FINDSTRINGEXACT", 0x01A2);g.Set("LB_SETLOCALE", 0x01A5);g.Set("LB_GETLOCALE", 0x01A6);g.Set("LB_SETCOUNT", 0x01A7);g.Set("LB_INITSTORAGE", 0x01A8);g.Set("LB_ITEMFROMPOINT", 0x01A9);g.Set("LB_MULTIPLEADDSTRING", 0x01B1);g.Set("LB_GETLISTBOXINFO", 0x01B2);g.Set("LB_MSGMAX", 0x01B3);

  /*
   * Edit Control Styles
   */
  g.Set("LBS_NOTIFY", 0x0001L);g.Set("LBS_SORT", 0x0002L);g.Set("LBS_NOREDRAW", 0x0004L);g.Set("LBS_MULTIPLESEL", 0x0008L);g.Set("LBS_OWNERDRAWFIXED", 0x0010L);g.Set("LBS_OWNERDRAWVARIABLE", 0x0020L);g.Set("LBS_HASSTRINGS", 0x0040L);g.Set("LBS_USETABSTOPS", 0x0080L);g.Set("LBS_NOINTEGRALHEIGHT", 0x0100L);g.Set("LBS_MULTICOLUMN", 0x0200L);g.Set("LBS_WANTKEYBOARDINPUT", 0x0400L);g.Set("LBS_EXTENDEDSEL", 0x0800L);g.Set("LBS_DISABLENOSCROLL", 0x1000L);g.Set("LBS_NODATA", 0x2000L);g.Set("LBS_NOSEL", 0x4000L);g.Set("LBS_COMBOBOX", 0x8000L);g.Set("LBS_STANDARD", (LBS_NOTIFY | LBS_SORT | WS_VSCROLL | WS_BORDER));

  /*
   * Listbox Notification Codes
   */
  g.Set("LBN_ERRSPACE", (-2));g.Set("LBN_SELCHANGE", 1);g.Set("LBN_DBLCLK", 2);g.Set("LBN_SELCANCEL", 3);g.Set("LBN_SETFOCUS", 4);g.Set("LBN_KILLFOCUS", 5);

  /*
   * Scroll Bar Styles
   */
  g.Set("SBS_HORZ", 0x0000L);g.Set("SBS_VERT", 0x0001L);g.Set("SBS_TOPALIGN", 0x0002L);g.Set("SBS_LEFTALIGN", 0x0002L);g.Set("SBS_BOTTOMALIGN", 0x0004L);g.Set("SBS_RIGHTALIGN", 0x0004L);g.Set("SBS_SIZEBOXTOPLEFTALIGN", 0x0002L);g.Set("SBS_SIZEBOXBOTTOMRIGHTALIGN", 0x0004L);g.Set("SBS_SIZEBOX", 0x0008L);g.Set("SBS_SIZEGRIP", 0x0010L);

  /*
   * Static Control Constants
   */
  g.Set("SS_LEFT", 0x00000000L);g.Set("SS_CENTER", 0x00000001L);g.Set("SS_RIGHT", 0x00000002L);g.Set("SS_ICON", 0x00000003L);g.Set("SS_BLACKRECT", 0x00000004L);g.Set("SS_GRAYRECT", 0x00000005L);g.Set("SS_WHITERECT", 0x00000006L);g.Set("SS_BLACKFRAME", 0x00000007L);g.Set("SS_GRAYFRAME", 0x00000008L);g.Set("SS_WHITEFRAME", 0x00000009L);g.Set("SS_USERITEM", 0x0000000AL);g.Set("SS_SIMPLE", 0x0000000BL);g.Set("SS_LEFTNOWORDWRAP", 0x0000000CL);g.Set("SS_OWNERDRAW", 0x0000000DL);g.Set("SS_BITMAP", 0x0000000EL);g.Set("SS_ENHMETAFILE", 0x0000000FL);g.Set("SS_ETCHEDHORZ", 0x00000010L);g.Set("SS_ETCHEDVERT", 0x00000011L);g.Set("SS_ETCHEDFRAME", 0x00000012L);g.Set("SS_TYPEMASK", 0x0000001FL);g.Set("SS_REALSIZECONTROL", 0x00000040L);g.Set("SS_NOPREFIX", 0x00000080L);g.Set("SS_NOTIFY", 0x00000100L);g.Set("SS_CENTERIMAGE", 0x00000200L);g.Set("SS_RIGHTJUST", 0x00000400L);g.Set("SS_REALSIZEIMAGE", 0x00000800L);g.Set("SS_SUNKEN", 0x00001000L);g.Set("SS_EDITCONTROL", 0x00002000L);g.Set("SS_ENDELLIPSIS", 0x00004000L);g.Set("SS_PATHELLIPSIS", 0x00008000L);g.Set("SS_WORDELLIPSIS", 0x0000C000L);g.Set("SS_ELLIPSISMASK", 0x0000C000L);

  /*
   * Window field offsets for GetWindowLong()
   */
  g.Set("GWL_WNDPROC", (-4));g.Set("GWL_HINSTANCE", (-6));g.Set("GWL_HWNDPARENT", (-8));g.Set("GWL_STYLE", (-16));g.Set("GWL_EXSTYLE", (-20));g.Set("GWL_USERDATA", (-21));g.Set("GWL_ID", (-12));

  /*
   * _WIN64 Window field offsets for GetWindowLong()
   */
  g.Set("GWLP_WNDPROC", (-4));g.Set("GWLP_HINSTANCE", (-6));g.Set("GWLP_HWNDPARENT", (-8));g.Set("GWLP_USERDATA", (-21));g.Set("GWLP_ID", (-12));

  /*
   * key State Masks for Mouse Messages
   */
  g.Set("MK_LBUTTON", 0x0001);g.Set("MK_RBUTTON", 0x0002);g.Set("MK_SHIFT", 0x0004);g.Set("MK_CONTROL", 0x0008);g.Set("MK_MBUTTON", 0x0010);g.Set("MK_XBUTTON1", 0x0020);g.Set("MK_XBUTTON2", 0x0040);

  /*
   * Edit Control Notification Codes
   */
  g.Set("EN_SETFOCUS", 0x0100);g.Set("EN_KILLFOCUS", 0x0200);g.Set("EN_CHANGE", 0x0300);g.Set("EN_UPDATE", 0x0400);g.Set("EN_ERRSPACE", 0x0500);g.Set("EN_MAXTEXT", 0x0501);g.Set("EN_HSCROLL", 0x0601);g.Set("EN_VSCROLL", 0x0602);g.Set("EN_ALIGN_LTR_EC", 0x0700);g.Set("EN_ALIGN_RTL_EC", 0x0701);g.Set("EN_BEFORE_PASTE", 0x0800);g.Set("EN_AFTER_PASTE", 0x0801);

  /*
   * Virtual Keys
   */
  g.Set("VK_LBUTTON", 0x01);g.Set("VK_RBUTTON", 0x02);g.Set("VK_CANCEL", 0x03);g.Set("VK_MBUTTON", 0x04);g.Set("VK_XBUTTON1", 0x05);g.Set("VK_XBUTTON2", 0x06);g.Set("VK_BACK", 0x08);g.Set("VK_TAB", 0x09);g.Set("VK_CLEAR", 0x0C);g.Set("VK_RETURN", 0x0D);g.Set("VK_SHIFT", 0x10);g.Set("VK_CONTROL", 0x11);g.Set("VK_MENU", 0x12);g.Set("VK_PAUSE", 0x13);g.Set("VK_CAPITAL", 0x14);g.Set("VK_KANA", 0x15);g.Set("VK_HANGEUL", 0x15);g.Set("VK_HANGUL", 0x15);g.Set("VK_JUNJA", 0x17);g.Set("VK_FINAL", 0x18);g.Set("VK_HANJA", 0x19);g.Set("VK_KANJI", 0x19);g.Set("VK_ESCAPE", 0x1B);g.Set("VK_CONVERT", 0x1C);g.Set("VK_NONCONVERT", 0x1D);g.Set("VK_ACCEPT", 0x1E);g.Set("VK_MODECHANGE", 0x1F);g.Set("VK_SPACE", 0x20);g.Set("VK_PRIOR", 0x21);g.Set("VK_NEXT", 0x22);g.Set("VK_END", 0x23);g.Set("VK_HOME", 0x24);g.Set("VK_LEFT", 0x25);g.Set("VK_UP", 0x26);g.Set("VK_RIGHT", 0x27);g.Set("VK_DOWN", 0x28);g.Set("VK_SELECT", 0x29);g.Set("VK_PRINT", 0x2A);g.Set("VK_EXECUTE", 0x2B);g.Set("VK_SNAPSHOT", 0x2C);g.Set("VK_INSERT", 0x2D);g.Set("VK_DELETE", 0x2E);g.Set("VK_HELP", 0x2F);g.Set("VK_LWIN", 0x5B);g.Set("VK_RWIN", 0x5C);g.Set("VK_APPS", 0x5D);g.Set("VK_SLEEP", 0x5F);g.Set("VK_NUMPAD0", 0x60);g.Set("VK_NUMPAD1", 0x61);g.Set("VK_NUMPAD2", 0x62);g.Set("VK_NUMPAD3", 0x63);g.Set("VK_NUMPAD4", 0x64);g.Set("VK_NUMPAD5", 0x65);g.Set("VK_NUMPAD6", 0x66);g.Set("VK_NUMPAD7", 0x67);g.Set("VK_NUMPAD8", 0x68);g.Set("VK_NUMPAD9", 0x69);g.Set("VK_MULTIPLY", 0x6A);g.Set("VK_ADD", 0x6B);g.Set("VK_SEPARATOR", 0x6C);g.Set("VK_SUBTRACT", 0x6D);g.Set("VK_DECIMAL", 0x6E);g.Set("VK_DIVIDE", 0x6F);g.Set("VK_F1", 0x70);g.Set("VK_F2", 0x71);g.Set("VK_F3", 0x72);g.Set("VK_F4", 0x73);g.Set("VK_F5", 0x74);g.Set("VK_F6", 0x75);g.Set("VK_F7", 0x76);g.Set("VK_F8", 0x77);g.Set("VK_F9", 0x78);g.Set("VK_F10", 0x79);g.Set("VK_F11", 0x7A);g.Set("VK_F12", 0x7B);g.Set("VK_F13", 0x7C);g.Set("VK_F14", 0x7D);g.Set("VK_F15", 0x7E);g.Set("VK_F16", 0x7F);g.Set("VK_F17", 0x80);g.Set("VK_F18", 0x81);g.Set("VK_F19", 0x82);g.Set("VK_F20", 0x83);g.Set("VK_F21", 0x84);g.Set("VK_F22", 0x85);g.Set("VK_F23", 0x86);g.Set("VK_F24", 0x87);g.Set("VK_NAVIGATION_VIEW", 0x88);g.Set("VK_NAVIGATION_MENU", 0x89);g.Set("VK_NAVIGATION_UP", 0x8A);g.Set("VK_NAVIGATION_DOWN", 0x8B);g.Set("VK_NAVIGATION_LEFT", 0x8C);g.Set("VK_NAVIGATION_RIGHT", 0x8D);g.Set("VK_NAVIGATION_ACCEPT", 0x8E);g.Set("VK_NAVIGATION_CANCEL", 0x8F);g.Set("VK_NUMLOCK", 0x90);g.Set("VK_SCROLL", 0x91);g.Set("VK_OEM_NEC_EQUAL", 0x92);g.Set("VK_OEM_FJ_JISHO", 0x92);g.Set("VK_OEM_FJ_MASSHOU", 0x93);g.Set("VK_OEM_FJ_TOUROKU", 0x94);g.Set("VK_OEM_FJ_LOYA", 0x95);g.Set("VK_OEM_FJ_ROYA", 0x96);g.Set("VK_LSHIFT", 0xA0);g.Set("VK_RSHIFT", 0xA1);g.Set("VK_LCONTROL", 0xA2);g.Set("VK_RCONTROL", 0xA3);g.Set("VK_LMENU", 0xA4);g.Set("VK_RMENU", 0xA5);g.Set("VK_BROWSER_BACK", 0xA6);g.Set("VK_BROWSER_FORWARD", 0xA7);g.Set("VK_BROWSER_REFRESH", 0xA8);g.Set("VK_BROWSER_STOP", 0xA9);g.Set("VK_BROWSER_SEARCH", 0xAA);g.Set("VK_BROWSER_FAVORITES", 0xAB);g.Set("VK_BROWSER_HOME", 0xAC);g.Set("VK_VOLUME_MUTE", 0xAD);g.Set("VK_VOLUME_DOWN", 0xAE);g.Set("VK_VOLUME_UP", 0xAF);g.Set("VK_MEDIA_NEXT_TRACK", 0xB0);g.Set("VK_MEDIA_PREV_TRACK", 0xB1);g.Set("VK_MEDIA_STOP", 0xB2);g.Set("VK_MEDIA_PLAY_PAUSE", 0xB3);g.Set("VK_LAUNCH_MAIL", 0xB4);g.Set("VK_LAUNCH_MEDIA_SELECT", 0xB5);g.Set("VK_LAUNCH_APP1", 0xB6);g.Set("VK_LAUNCH_APP2", 0xB7);g.Set("VK_OEM_1", 0xBA);g.Set("VK_OEM_PLUS", 0xBB);g.Set("VK_OEM_COMMA", 0xBC);g.Set("VK_OEM_MINUS", 0xBD);g.Set("VK_OEM_PERIOD", 0xBE);g.Set("VK_OEM_2", 0xBF);g.Set("VK_OEM_3", 0xC0);g.Set("VK_GAMEPAD_A", 0xC3);g.Set("VK_GAMEPAD_B", 0xC4);g.Set("VK_GAMEPAD_X", 0xC5);g.Set("VK_GAMEPAD_Y", 0xC6);g.Set("VK_GAMEPAD_RIGHT_SHOULDER", 0xC7);g.Set("VK_GAMEPAD_LEFT_SHOULDER", 0xC8);g.Set("VK_GAMEPAD_LEFT_TRIGGER", 0xC9);g.Set("VK_GAMEPAD_RIGHT_TRIGGER", 0xCA);g.Set("VK_GAMEPAD_DPAD_UP", 0xCB);g.Set("VK_GAMEPAD_DPAD_DOWN", 0xCC);g.Set("VK_GAMEPAD_DPAD_LEFT", 0xCD);g.Set("VK_GAMEPAD_DPAD_RIGHT", 0xCE);g.Set("VK_GAMEPAD_MENU", 0xCF);g.Set("VK_GAMEPAD_VIEW", 0xD0);g.Set("VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON", 0xD1);g.Set("VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON", 0xD2);g.Set("VK_GAMEPAD_LEFT_THUMBSTICK_UP", 0xD3);g.Set("VK_GAMEPAD_LEFT_THUMBSTICK_DOWN", 0xD4);g.Set("VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT", 0xD5);g.Set("VK_GAMEPAD_LEFT_THUMBSTICK_LEFT", 0xD6);g.Set("VK_GAMEPAD_RIGHT_THUMBSTICK_UP", 0xD7);g.Set("VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN", 0xD8);g.Set("VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT", 0xD9);g.Set("VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT", 0xDA);g.Set("VK_OEM_4", 0xDB);g.Set("VK_OEM_5", 0xDC);g.Set("VK_OEM_6", 0xDD);g.Set("VK_OEM_7", 0xDE);g.Set("VK_OEM_8", 0xDF);g.Set("VK_OEM_AX", 0xE1);g.Set("VK_OEM_102", 0xE2);g.Set("VK_ICO_HELP", 0xE3);g.Set("VK_ICO_00", 0xE4);g.Set("VK_PROCESSKEY", 0xE5);g.Set("VK_ICO_CLEAR", 0xE6);g.Set("VK_PACKET", 0xE7);g.Set("VK_OEM_RESET", 0xE9);g.Set("VK_OEM_JUMP", 0xEA);g.Set("VK_OEM_PA1", 0xEB);g.Set("VK_OEM_PA2", 0xEC);g.Set("VK_OEM_PA3", 0xED);g.Set("VK_OEM_WSCTRL", 0xEE);g.Set("VK_OEM_CUSEL", 0xEF);g.Set("VK_OEM_ATTN", 0xF0);g.Set("VK_OEM_FINISH", 0xF1);g.Set("VK_OEM_COPY", 0xF2);g.Set("VK_OEM_AUTO", 0xF3);g.Set("VK_OEM_ENLW", 0xF4);g.Set("VK_OEM_BACKTAB", 0xF5);g.Set("VK_ATTN", 0xF6);g.Set("VK_CRSEL", 0xF7);g.Set("VK_EXSEL", 0xF8);g.Set("VK_EREOF", 0xF9);g.Set("VK_PLAY", 0xFA);g.Set("VK_ZOOM", 0xFB);g.Set("VK_NONAME", 0xFC);g.Set("VK_PA1", 0xFD);g.Set("VK_OEM_CLEAR", 0xFE);
g.Set("VK_0", 48);g.Set("VK_1", 49);g.Set("VK_2", 50);g.Set("VK_3", 51);g.Set("VK_4", 52);g.Set("VK_5", 53);g.Set("VK_6", 54);g.Set("VK_7", 55);g.Set("VK_8", 56);g.Set("VK_9", 57);g.Set("VK_A", 65);g.Set("VK_B", 66);g.Set("VK_C", 67);g.Set("VK_D", 68);g.Set("VK_E", 69);g.Set("VK_F", 70);g.Set("VK_G", 71);g.Set("VK_H", 72);g.Set("VK_I", 73);g.Set("VK_J", 74);g.Set("VK_K", 75);g.Set("VK_L", 76);g.Set("VK_M", 77);g.Set("VK_N", 78);g.Set("VK_O", 79);g.Set("VK_P", 80);g.Set("VK_Q", 81);g.Set("VK_R", 82);g.Set("VK_S", 83);g.Set("VK_T", 84);g.Set("VK_U", 85);g.Set("VK_V", 86);g.Set("VK_W", 87);g.Set("VK_X", 88);g.Set("VK_Y", 89);g.Set("VK_Z", 90);
  /*
   * Stock Logical Objects
   */
  g.Set("OBJ_PEN", 1);g.Set("OBJ_BRUSH", 2);g.Set("OBJ_FONT", 6);g.Set("MONO_FONT", 8);g.Set("WHITE_BRUSH", 0);g.Set("LTGRAY_BRUSH", 1);g.Set("GRAY_BRUSH", 2);g.Set("DKGRAY_BRUSH", 3);g.Set("BLACK_BRUSH", 4);g.Set("NULL_BRUSH", 5);g.Set("HOLLOW_BRUSH", NULL_BRUSH);g.Set("WHITE_PEN", 6);g.Set("BLACK_PEN", 7);g.Set("NULL_PEN", 8);g.Set("OEM_FIXED_FONT", 10);g.Set("ANSI_FIXED_FONT", 11);g.Set("ANSI_VAR_FONT", 12);g.Set("SYSTEM_FONT", 13);g.Set("DEVICE_DEFAULT_FONT", 14);g.Set("DEFAULT_PALETTE", 15);g.Set("SYSTEM_FIXED_FONT", 16);g.Set("DEFAULT_GUI_FONT", 17);g.Set("DC_BRUSH", 18);g.Set("DC_PEN", 19);g.Set("RC_PALETTE", 0x0100);g.Set("PFD_NEED_PALETTE", 0x00000080);g.Set("PFD_NEED_SYSTEM_PALETTE", 0x00000100);

  /*
   * winnt.h
   */
  g.Set("PAGE_NOACCESS", 0x01);g.Set("PAGE_READONLY", 0x02);g.Set("PAGE_READWRITE", 0x04);g.Set("PAGE_WRITECOPY", 0x08);g.Set("PAGE_EXECUTE", 0x10);g.Set("PAGE_EXECUTE_READ", 0x20);g.Set("PAGE_EXECUTE_READWRITE", 0x40);g.Set("PAGE_EXECUTE_WRITECOPY", 0x80);g.Set("PAGE_GUARD", 0x100);g.Set("PAGE_NOCACHE", 0x200);g.Set("PAGE_WRITECOMBINE", 0x400);g.Set("PAGE_GRAPHICS_NOACCESS", 0x0800);g.Set("PAGE_GRAPHICS_READONLY", 0x1000);g.Set("PAGE_GRAPHICS_READWRITE", 0x2000);g.Set("PAGE_GRAPHICS_EXECUTE", 0x4000);g.Set("PAGE_GRAPHICS_EXECUTE_READ", 0x8000);g.Set("PAGE_GRAPHICS_EXECUTE_READWRITE", 0x10000);g.Set("PAGE_GRAPHICS_COHERENT", 0x20000);g.Set("PAGE_ENCLAVE_THREAD_CONTROL", 0x80000000);g.Set("PAGE_REVERT_TO_FILE_MAP", 0x80000000);g.Set("PAGE_TARGETS_NO_UPDATE", 0x40000000);g.Set("PAGE_TARGETS_INVALID", 0x40000000);g.Set("PAGE_ENCLAVE_UNVALIDATED", 0x20000000);g.Set("PAGE_ENCLAVE_DECOMMIT", 0x10000000);g.Set("MEM_COMMIT", 0x00001000);g.Set("MEM_RESERVE", 0x00002000);g.Set("MEM_REPLACE_PLACEHOLDER", 0x00004000);g.Set("MEM_RESERVE_PLACEHOLDER", 0x00040000);g.Set("MEM_RESET", 0x00080000);g.Set("MEM_TOP_DOWN", 0x00100000);g.Set("MEM_WRITE_WATCH", 0x00200000);g.Set("MEM_PHYSICAL", 0x00400000);g.Set("MEM_ROTATE", 0x00800000);g.Set("MEM_DIFFERENT_IMAGE_BASE_OK", 0x00800000);g.Set("MEM_RESET_UNDO", 0x01000000);g.Set("MEM_LARGE_PAGES", 0x20000000);g.Set("MEM_4MB_PAGES", 0x80000000);g.Set("MEM_64K_PAGES", (MEM_LARGE_PAGES | MEM_PHYSICAL));g.Set("MEM_UNMAP_WITH_TRANSIENT_BOOST", 0x00000001);g.Set("MEM_COALESCE_PLACEHOLDERS", 0x00000001);g.Set("MEM_PRESERVE_PLACEHOLDER", 0x00000002);g.Set("MEM_DECOMMIT", 0x00004000);g.Set("MEM_RELEASE", 0x00008000);g.Set("MEM_FREE", 0x00010000);g.Set("MEM_EXTENDED_PARAMETER_GRAPHICS", 0x00000001);g.Set("MEM_EXTENDED_PARAMETER_NONPAGED", 0x00000002);g.Set("MEM_EXTENDED_PARAMETER_ZERO_PAGES_OPTIONAL", 0x00000004);g.Set("MEM_EXTENDED_PARAMETER_NONPAGED_LARGE", 0x00000008);g.Set("MEM_EXTENDED_PARAMETER_NONPAGED_HUGE", 0x00000010);g.Set("MEM_EXTENDED_PARAMETER_NUMA_NODE_MANDATORY", MINLONG64);g.Set("MEM_EXTENDED_PARAMETER_TYPE_BITS", 8);g.Set("MEM_PRIVATE", 0x00020000);g.Set("MEM_MAPPED", 0x00040000);g.Set("MEM_IMAGE", 0x01000000);


  nm_retu;
}
