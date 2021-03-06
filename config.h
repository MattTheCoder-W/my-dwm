/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;	/* gaps size between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 34;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Roboto Mono:size=14", "Inconsolata Nerd Font Mono:size=20" };
static const char dmenufont[]       = "Roboto Mono:size=14";
static const char col_gray1[]       = "#383c4a";
static const char col_gray2[]       = "#404552";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#7c818c"; /* "#ff7b00"; */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "mpv",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/terminator", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "/usr/bin/urxvt", NULL };
static const char *firefox[] = { "firefox", NULL };

static const char *exit_menu[] = { "/usr/local/share/dwm/exit_menu.sh", NULL };

/* Volume control */
// static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
// static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
// static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *upvol[] = { "/usr/local/share/dwm/volume.sh", "small-up", NULL };
static const char *downvol[] = { "/usr/local/share/dwm/volume.sh", "small-down", NULL };

static const char *upvolbig[] = { "/usr/local/share/dwm/volume.sh", "up", NULL };
static const char *downvolbig[] = { "/usr/local/share/dwm/volume.sh", "down", NULL };

static const char *mutevol[] = { "/usr/local/share/dwm/volume.sh", "mute", NULL };

/* Print Screen - Flameshot */
static const char *flameshot[] = { "/usr/bin/flameshot", "gui", NULL };

/* Restart autostart script - kill bar and start autostart */
static const char *reconf[] = { "/usr/local/share/dwm/reconf", NULL };

/* Media Keys */
static const char *playpause[] = {"/usr/bin/playerctl", "play-pause", NULL};
static const char *playnext[] = {"/usr/bin/playerctl", "next", NULL};
static const char *playprev[] = {"/usr/bin/playerctl", "previous", NULL};

/* Other */
static const char *change_wall[] = {"/home/m4t1/.config/dwm/change.sh", NULL};
static const char *disable_screen[] = {"/home/m4t1/.config/dwm/disable-screen.sh", NULL};

#include <X11/XF86keysym.h>  // Volume buttons
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,				XK_f,	   spawn,		   {.v = firefox } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
 	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
 	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,						XK_n,	   shiftview,	   {.i = +1 } },
	{ MODKEY,						XK_b,	   shiftview,	   {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_Escape, quit,      	   {0} },
	{ 0,              XF86XK_AudioLowerVolume, spawn, 		   {.v = downvolbig } },
	{ 0,              XF86XK_AudioMute, 	   spawn, 		   {.v = mutevol } },
	{ ShiftMask,      XF86XK_AudioLowerVolume, spawn, 		   {.v = downvol } },
	{ 0,              XF86XK_AudioRaiseVolume, spawn, 		   {.v = upvolbig } },
	{ ShiftMask,      XF86XK_AudioRaiseVolume, spawn, 		   {.v = upvol } },
	{ 0,              XF86XK_AudioPlay, 	   spawn, 		   {.v = playpause } },
	{ 0,              XF86XK_AudioNext, 	   spawn, 		   {.v = playnext } },
	{ 0,              XF86XK_AudioPrev, 	   spawn, 		   {.v = playprev } },
	{ 0,							XK_Print,  spawn,	   	   {.v = flameshot } },
	{ MODKEY|ShiftMask,				XK_r,	   spawn,		   {.v = reconf } },
	{ MODKEY,						XK_f,	   togglefullscr,  {0} },
	{ MODKEY|ShiftMask,		XK_k,	   spawn,	   {.v = exit_menu} },
	{ MODKEY|ShiftMask,		XK_a,	   spawn,	   {.v = change_wall} },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,	   {.v = disable_screen} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

