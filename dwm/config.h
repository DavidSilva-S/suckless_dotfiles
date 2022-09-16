/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 30;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "HackNerdFont:style=Regular:pixelsize=16:antialias=true" };
static const char dmenufont[]       = "HackNerdFont:style=Regular:pixelsize=16:antialias=true";
//static const unsigned int baralpha = 2;
//static const unsigned int borderalpha = 1;
static char dmenumon[2] = "0";

/*theme dark blue*/
static const char col_rich_black_fogra_39[] = "#02050C";
static const char col_rich_black_fogra_29[] = "#082E69";
static const char col_green_blue[] = "#2F68A4";

/*them dark purple*/
static const char purple[] = "#6F20A5";
static const char blue_munsell[] = "#2A8FAE";

/*color default*/
static const char col_gray1[]       = "#000001";
static const char col_gray2[]       = "#444444"; 
static const char col_gray4[]       = "#2F68A4";
static const char col_cyan[]        = "#000037";
static const char col_white[]       = "#bbbbbb";


 
static const char *colors[][3]      = {
	/*             fg           bg                       border   */
	[SchemeNorm] = { blue_munsell, col_rich_black_fogra_39, col_rich_black_fogra_39 },
	[SchemeSel]  = { blue_munsell, purple,                  purple},
};
 
//static const unsigned int alphas[][3]      = {
//	/*               fg      bg        border     */
//	[SchemeNorm] = { OPACI, baralpha, borderalpha },
//	[SchemeSel]  = { OPACI, baralpha, borderalpha },
//};


#define ICONSIZE 20   /* icon size in pixels */
#define ICONSPACING 5 /* space (pixels) between icon and title */
#define GAP_TOGGLE 100
#define GAP_RESET  0

/* tagging */
static const char *tags[] = { "", "", "", "","ﭮ","",""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask   switchtotag    isfloating   monitor */
	{ "firefox",  NULL,       NULL,       1 << 1,                    0,           -1 },
	{ "st",       NULL,       NULL,       1 << 0,                    0,           -1 },
	{ "code-oss", NULL,       NULL,       1 << 5,                    0,           -1 },
	{ "Thunar",   NULL,       NULL,       1 << 3,                    0,           -1 },
	{ "discord",  NULL,       NULL,       1 << 4,                    0,           -1 },
	{ "virtualbox", NULL,     NULL,       1 << 6,                    0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
/* Vol control */
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };

/* Brightness control */
static const char *brinc[] = { "/usr/bin/light", "-A", "5", NULL };
static const char *brdec[] = { "/usr/bin/light", "-U", "5", NULL };

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *firefox[] = { "firefox", NULL };

/* Brightness Commands */
//static const char *brightness[][2] = {
//	{"xbacklight", "-inc", "5%", NULL},
//	{"xbacklight", "-dec", "5%", NULL}
//};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,                      quit,           {0} },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,          spawn, {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn, {.v = upvol   } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = brinc} },
        { 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = brdec} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
        { MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
        { MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
        { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        spawn,          {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

