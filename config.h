/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 6;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "CaskaydiaMonoNerdFontMono-SemiLight:size=10" };
static const char dmenufont[]       = "CaskaydiaMonoNerdFontMono-SemiLight:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char bloodred[]     = "#780606"; /* added */
static const char ajor[]     = "#924441"; /* added */
static const char pink[]     = "#FF0833"; /* added */
static const char seal_brown[]     = "#321414"; /* added */
static const char pullman_brown[]     = "#644117"; /* added */
static const char cyan[]     = "#008b8b"; /* added */
static const char dark[]     = "#000000"; /* added */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, pullman_brown, col_gray2 },
	[SchemeSel]  = { col_gray4, dark, cyan },
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

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define SUPER Mod4Mask
#define Alt   Mod1Mask

/* Mod4Mask = (super/meta/windows) key, Mod1Mask = alt, ControlMask = ctrl, ShiftMask = shift */

#define TAGKEYS(KEY,TAG) \
	{ SUPER,                           KEY,      view,           {.ui = 1 << TAG} }, \
	{ SUPER|ControlMask,               KEY,      toggleview,     {.ui = 1 << TAG} }, \
	/* after selected window puted in all tags, this line will remove window from all tags exept KEY tag */ \
	{ SUPER|ShiftMask,                 KEY,      tag,            {.ui = 1 << TAG} }, \
	/* after selected window puted in all tags, this line will remove window from KEY tag */ \
	{ SUPER|ControlMask|ShiftMask,     KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { "librewolf", NULL };

#include <X11/XF86keysym.h>

static const Key keys[] = {
	TAGKEYS(                       XK_1,                      0)
	TAGKEYS(                       XK_2,                      1)
	TAGKEYS(                       XK_3,                      2)
	TAGKEYS(                       XK_4,                      3)
	TAGKEYS(                       XK_5,                      4)
	TAGKEYS(                       XK_6,                      5)
	TAGKEYS(                       XK_7,                      6)
	TAGKEYS(                       XK_8,                      7)
	TAGKEYS(                       XK_9,                      8)

	/* modifier                    key        function        argument */
	{ SUPER,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ SUPER,                       XK_Return, spawn,          {.v = termcmd } },
	{ SUPER,                       XK_b,      togglebar,      {0} },
	{ SUPER,                       XK_j,      focusstack,     {.i = +1 } },
	{ SUPER,                       XK_k,      focusstack,     {.i = -1 } },
	{ SUPER,                       XK_i,      incnmaster,     {.i = +1 } },
	{ SUPER,                       XK_d,      incnmaster,     {.i = -1 } }, /* default: XK_d */
	{ SUPER,                       XK_h,      setmfact,       {.f = -0.05} },
	{ SUPER,                       XK_l,      setmfact,       {.f = +0.05} },
	
	/* master selected window */
	{ SUPER|ShiftMask,             XK_Return, zoom,           {0} },
      	
	/* change between tags */	
	{ SUPER,                       XK_Tab,    view,           {0} }, 
	
	{ SUPER,                       XK_c,      killclient,     {0} },
	{ SUPER,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ SUPER,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ SUPER,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        
	/* change between tiling & floating, i.e. floating windows will tile if Alt|ShiftMask+XK_space is not set */ 
	{ SUPER,                       XK_space,  setlayout,      {0} },
        
	/* set selected window to floating and this window will not be effected by Alt+XK_space */ 	
	{ SUPER|ShiftMask,             XK_space,  togglefloating, {0} },
	
	/* view all tags */	
	{ SUPER,                       XK_0,      view,           {.ui = ~0 } },
	
	/* put selected window in all tags */	
	{ SUPER|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, 
	
	{ SUPER,                       XK_comma,  focusmon,       {.i = -1 } },
	{ SUPER,                       XK_period, focusmon,       {.i = +1 } },
	{ SUPER|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ SUPER|ShiftMask,             XK_period, tagmon,         {.i = +1 } },	
 	
	/* brightness control */	
	{ 0,                       XF86XK_MonBrightnessUp,  spawn,          SHCMD("brightnessctl set 1%+ && pkill -RTMIN+2 dwmblocks") },
	{ 0,                       XF86XK_MonBrightnessDown,  spawn,          SHCMD("brightnessctl set 1%- && pkill -RTMIN+2 dwmblocks") },
	
	/* audio control */	
	{ 0,                       XF86XK_AudioRaiseVolume, spawn,       SHCMD("pamixer -i 2 && pkill -RTMIN+5 dwmblocks") },
	{ 0,                       XF86XK_AudioLowerVolume,  spawn,          SHCMD("pamixer -d 2 && pkill -RTMIN+5 dwmblocks") },
	{ 0,                       XF86XK_AudioMute, spawn,          SHCMD("pamixer -t && pkill -RTMIN+5 dwmblocks") },
	
  	{ SUPER,                       XK_s,       spawn,         { .v = browsercmd } }, /* default browser */	

	/* keyboard layout signal */
	{ Alt|ShiftMask,	       0,	   spawn,	  SHCMD("pkill -RTMIN+9 dwmblocks") },
	
	/* exit dwm */	
	{ SUPER|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         SUPER,          Button1,        movemouse,      {0} },
	{ ClkClientWin,         SUPER,          Button2,        togglefloating, {0} },
	{ ClkClientWin,         SUPER,          Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            SUPER,          Button1,        tag,            {0} },
	{ ClkTagBar,            SUPER,          Button3,        toggletag,      {0} },
};

