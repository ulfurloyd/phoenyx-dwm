/* See LICENSE file for copyright and license details. */

#include "/home/wolf/.cache/wal/colors-wal-dwm.h"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 8;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = { "Fira Code Nerd Font Mono:size=12" };
static const char dmenufont[]       = "Fira Code Nerd Font Mono:size=12";

static const char *const autostart[] = {
	"dwmblocks", NULL,
    "picom", NULL,
	"sh", "-c", "~/.screenlayout/test.sh", NULL,
    "wal-bg", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *roficmd[] = { "rofi", "-show", "combi", "-modes", "combi", "-combi-modes", "'window,drun,run'", NULL };
static const char *termcmd[]  = { "kitty", NULL };

static const Key keys[] = {
	/* modifier                 key                function        argument */
	{ MODKEY,                   XK_space,          spawn,          {.v = roficmd } },
	{ MODKEY,                   XK_Return,         spawn,          {.v = termcmd } },
	{ MODKEY,                   XK_b,              togglebar,      {0} },
	{ MODKEY,                   XK_j,              focusstack,     {.i = +1 } },
	{ MODKEY,                   XK_k,              focusstack,     {.i = -1 } },
	{ MODKEY,                   XK_i,              incnmaster,     {.i = +1 } },
	{ MODKEY,                   XK_d,              incnmaster,     {.i = -1 } },
	{ MODKEY,                   XK_h,              setmfact,       {.f = -0.05} },
	{ MODKEY,                   XK_l,              setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,         XK_Return,         zoom,           {0} },
	{ MODKEY,                   XK_Tab,            view,           {0} },
	{ MODKEY,                   XK_w,              killclient,     {0} },
	{ MODKEY,                   XK_t,              togglefloating, {0} },
	{ MODKEY,                   XK_f,              togglefullscr,  {0} },
	{ MODKEY,                   XK_0,              view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,         XK_0,              tag,            {.ui = ~0 } },
	{ MODKEY,                   XK_bracketleft,    focusmon,       {.i = -1 } },
	{ MODKEY,                   XK_bracketright,   focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,         XK_bracketleft,    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,         XK_bracketright,   tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,       XK_minus,          setgaps,        {.i = -1 } },
	{ MODKEY|ControlMask,       XK_equal,          setgaps,        {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask,         XK_equal,          setgaps,        {.i = 0  } },
    { MODKEY,                   XK_equal,          spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
    { MODKEY,                   XK_minus,          spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
	{ MODKEY,                   XK_m,              spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
	TAGKEYS(                    XK_1,                              0)
	TAGKEYS(                    XK_2,                              1)
	TAGKEYS(                    XK_3,                              2)
	TAGKEYS(                    XK_4,                              3)
	TAGKEYS(                    XK_5,                              4)
	TAGKEYS(                    XK_6,                              5)
	TAGKEYS(                    XK_7,                              6)
	TAGKEYS(                    XK_8,                              7)
	TAGKEYS(                    XK_9,                              8)
	{ MODKEY|ShiftMask,         XK_q,              quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

