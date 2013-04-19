/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = DEFAULT_FONT;
static const char normbordercolor[] = NORMAL_WIN_BORDER;
static const char normbordercolorF[]= NORMAL_WIN_BORDER_FLOAT;
static const char normbgcolor[]     = NORMAL_BACKGROUND;
static const char normfgcolor[]     = NORMAL_FOREGROUND;
static const char selbordercolor[]  = SELECTED_WIN_BORDER;
static const char selbordercolorF[] = SELECTED_WIN_BORDER_FLOAT;
static const char selbgcolor[]      = SELECTED_BACKGROUND;
static const char selfgcolor[]      = SELECTED_FOREGROUND;
static const char urgbordercolor[]  = URGENT_WIN_BORDER;
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool autoLayout        = True;     /* False means don't drop layout while switching */
/* runtime configured apperance */
static Bool autoFocus               = True;     /* False means no autofocusing windows by mouse pointer */

/* Systray */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "opera",     NULL,       NULL,       1 << 1,       True,        -1 },
	{ "Opera",     NULL,       NULL,       1 << 1,       True,        -1 },
	{ "luakit",    NULL,       NULL,       1 << 1,       True,        -1 },
	{ "fbpanel",   NULL,       NULL,       ~0,           True,        -1 },
	{ "osmo",      NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#ifdef NATIVE_XKB_SWITCH
/* XKB layouts */
static const XkbLayout xkb_groups[] = {
	{ XkbGroup1Index, NULL }, /* always base */
	{ XkbGroup2Index, NULL },
	{ XkbGroup3Index, NULL },
	{ XkbGroup4Index, NULL }
};
#define KXB_ALTR_DEFAULT XkbGroup2Index
#endif

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "><>",      NULL },       /* first entry is default. NULL is floating*/
	{ "[M]",      monocle },    /* a-la FullScreen */   
	{ "[]=",      tile },       /* Tiling  */
	{ "HHH",      grid },       /* Grid */
	{ "TTT",      bstack },     /* BiStack Normal */
	{ "===",      bstackhoriz },/* BiStack Horizontal */ 
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *xcmdline[]  = { "x-cmdline", NULL };
static const char *xlock[] = { "xscreensaver-command", "-lock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = xcmdline } },
	{ MODKEY,                       XK_l,      spawn,          {.v = xlock } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|ControlMask,           XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_Tab,    swapclients,    {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_s,      setlayout,      {.v = &layouts[5]} }, /* BiStack Horizontal */
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[4]} }, /* BiStack Normal */
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} }, /* Grid */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} }, /* Float */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} }, /* FullScreen */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[0]} }, /* Tile */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_a,      toggleautofocus,{0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_F10,    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_F10,    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_F1,                      0)
	TAGKEYS(                        XK_F2,                      1)
	TAGKEYS(                        XK_F3,                      2)
	TAGKEYS(                        XK_F4,                      3)
	TAGKEYS(                        XK_F5,                      4)
	TAGKEYS(                        XK_F6,                      5)
	TAGKEYS(                        XK_F7,                      6)
	TAGKEYS(                        XK_F8,                      7)
	TAGKEYS(                        XK_F9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {.i = 1 } },
	// Enhancements for window management
	{ MODKEY|ControlMask|ShiftMask, XK_l,      togglehorizontalmax,   { 0 } },
	{ MODKEY|ControlMask|ShiftMask, XK_k,      toggleverticalmax,     { 0 } },
	{ MODKEY|ControlMask,           XK_m,      togglemaximize,        { 0 } },
	{ MODKEY|ControlMask|ShiftMask, XK_w,      winspertag,            { 0 } },
	// Enable moving and resizing windows from the keybboard
	{ MODKEY,                       XK_Down,   moveresize,     { .v = "0x 10y 0w 0h"  }},
	{ MODKEY,                       XK_Up,     moveresize,     { .v = "0x -10y 0w 0h" }},
	{ MODKEY,                       XK_Right,  moveresize,     { .v = "10x 0y 0w 0h"  }},
	{ MODKEY,                       XK_Left,   moveresize,     { .v = "-10x 0y 0w 0h" }},
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     { .v = "0x 0y 0w 14h"  }},
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     { .v = "0x 0y 0w -14h" }},
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     { .v = "0x 0y 14w 0h"  }},
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     { .v = "0x 0y -14w 0h" }},
	// XKB additional layout
	{ MODKEY|ControlMask,           XK_equal,  switch_xkb,     {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[0]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = xcmdline } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
