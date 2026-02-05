/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */

static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int allowkill          = 1;        /* allow killing clients by default? */
static const char *fonts[]          = { "CaskaydiaMono NFM:size=12", "Noto Color Emoji:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "CaskaydiaMono NFM:size=12";
static const char col_gray1[]       = "#191919";
static const char col_gray2[]       = "#333333";
static const char col_gray3[]       = "#555555";
static const char col_gray4[]       = "#aaaaaa";
static const char col_gray5[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_redb[]        = "#660000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray5, /*col_gray1*/ col_cyan, /*col_redb*/ col_cyan },
};

// specify an app as scratchpad in scratchpads[], then optionaly specify a rule for it in rules[], then bind it to a keybind in keys[].
// if a scratchpad wanted to be removed just remove its keybind.
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"alacritty", "--class", "lf", "-e", "lfub", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"lf",          spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                 instance          title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",                NULL,             NULL,       0,            0,           1,           -1 },
	{ "Firefox",             NULL,             NULL,       0,            0,           0,           -1 },
	{ "mpv",                 NULL,             NULL,       0,            1,           1,           -1 },
	{ "Nsxiv",               NULL,             NULL,       0,            1,           1,           -1 },
	{ NULL,                  "spterm",         NULL,       SPTAG(0),     0,           1,           -1 },
	{ NULL,                  "lf",             NULL,       SPTAG(1),     0,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static const int attachdirection = 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "[D]",      deck }, /*H[]*/
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask /* Mod4Mask = `super` or `meta` or `windows` key | Mod1Mask = alt | ControlMask = ctrl | ShiftMask = shift */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, 

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "rofi", "-show", "drun" };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-i", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray5, NULL };
static const char *termcmd[]  = { "st", NULL };
#include "shift-tools-scratchpads.c"
#include "bulkill.c"
#include "movestack.c"
static const Key keys[] = {
    /* modifier                                     key                       function                       argument */
    { MODKEY,                                       XK_r,                     spawn,                         {.v = dmenucmd } },
    { MODKEY,                                       XK_Return,                spawn,                         {.v = termcmd } },
    { MODKEY,                                       XK_b,                     togglebar,                     {0} },
   
    { MODKEY,            			    XK_z,  	              togglescratch,                 {.ui = 0 } },
    //{ MODKEY|ShiftMask,            		    XK_e,	              togglescratch,                 {.ui = 1 } },

    { MODKEY|Mod1Mask,                              XK_s,                     togglesticky,                  {0} },
    
    { Mod1Mask,                                     XK_o,                     shiftviewclients,              { .i = +1 } },
    { Mod1Mask,	                                    XK_i,                     shiftviewclients,              { .i = -1 } },
    { Mod1Mask|ShiftMask,                           XK_o,                     shiftview,                     { .i = +1 } },
    { Mod1Mask|ShiftMask,                           XK_i,	                  shiftview,                     { .i = -1 } },
    { Mod1Mask,	                                    XK_l,                     shifttag,                      { .i = +1 } },
    { Mod1Mask,	                                    XK_k,                     shifttag,                      { .i = -1 } },
    { Mod1Mask|ShiftMask,	                    XK_l,                     shifttagclients,               { .i = +1 } },
    { Mod1Mask|ShiftMask,	                    XK_k,                     shifttagclients,               { .i = -1 } },
    { Mod1Mask,	                                    XK_period,                shiftboth,                     { .i = +1 } },
    { Mod1Mask,	                                    XK_comma,                 shiftboth,                     { .i = -1 } },
    { Mod1Mask|ShiftMask,	                    XK_period,                shiftswaptags,                 { .i = +1 } },
    { Mod1Mask|ShiftMask,	                    XK_comma,                 shiftswaptags,                 { .i = -1 } },
    
    { MODKEY,                                       XK_q,                     toggleallowkill,               {0} },
    
    { MODKEY|ControlMask,                           XK_j,                     movestack,                     {.i = +1 } },
    { MODKEY|ControlMask,                           XK_k,                     movestack,                     {.i = -1 } },
    
    { MODKEY,                                       XK_n,                     switchcol,                     {0} },
    
    { MODKEY|ControlMask|ShiftMask,                 XK_j,                     inplacerotate,                 {.i = +1} },
    { MODKEY|ControlMask|ShiftMask,                 XK_k,                     inplacerotate,                 {.i = -1} },
    { MODKEY|ControlMask|ShiftMask,                 XK_h,                     inplacerotate,                 {.i = +2} },
    { MODKEY|ControlMask|ShiftMask,                 XK_l,                     inplacerotate,                 {.i = -2} },
    
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

    { MODKEY,                                       XK_i,                     incnmaster,                    {.i = +1 } },
    { MODKEY,                                       XK_d,                     incnmaster,                    {.i = -1 } },
    { MODKEY,                                       XK_o,                     resetnmaster,                  {0} },
    { MODKEY,                                       XK_h,                     setmfact,                      {.f = -0.05} },
    { MODKEY,                                       XK_l,                     setmfact,                      {.f = +0.05} },
    { MODKEY|Mod1Mask,                              XK_Return,                zoom,                          {0} },
    
    { MODKEY|Mod1Mask,                              XK_u,                     incrgaps,                      {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,                    XK_u,                     incrgaps,                      {.i = -1 } },
    { MODKEY|Mod1Mask,                              XK_i,                     incrigaps,                     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,                    XK_i,                     incrigaps,                     {.i = -1 } },
    { MODKEY|Mod1Mask,                              XK_o,                     incrogaps,                     {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,                    XK_o,                     incrogaps,                     {.i = -1 } },
    { MODKEY|Mod1Mask,                              XK_6,                     incrihgaps,                    {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,                    XK_6,                     incrihgaps,                    {.i = -1 } },
    { MODKEY|Mod1Mask,                              XK_7,                     incrivgaps,                    {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,                    XK_7,                     incrivgaps,                    {.i = -1 } },
    { MODKEY|Mod1Mask,                              XK_8,                     incrohgaps,                    {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,                    XK_8,                     incrohgaps,                    {.i = -1 } },
    { MODKEY|Mod1Mask,                              XK_9,                     incrovgaps,                    {.i = +1 } },
    { MODKEY|Mod1Mask|ShiftMask,                    XK_9,                     incrovgaps,                    {.i = -1 } },
    { MODKEY|Mod1Mask,                              XK_0,                     togglegaps,                    {0} },
    { MODKEY|Mod1Mask|ShiftMask,                    XK_0,                     defaultgaps,                   {0} },
    
    { MODKEY,                                       XK_Tab,                   view,                          {0} },
    { MODKEY|ShiftMask,                             XK_c,                     killclient,                    {0} },
    { MODKEY|ControlMask,                           XK_c,                     bulkill,                       {.ui = 1} },  // kill unselect
    { MODKEY|ShiftMask|ControlMask,                 XK_c,                     bulkill,                       {.ui = 2} },  // killall
    
    { MODKEY,                                       XK_t,                     setlayout,                     {.v = &layouts[0]} }, // tile
    { MODKEY,                                       XK_f,                     setlayout,                     {.v = &layouts[1]} }, // float
    { MODKEY,                                       XK_m,                     setlayout,                     {.v = &layouts[2]} }, // monocle
    { MODKEY|ShiftMask,                             XK_backslash,             setlayout,                     {.v = &layouts[3]} }, // spiral
    { MODKEY,                                       XK_backslash,             setlayout,                     {.v = &layouts[4]} }, // dwindle 
    { MODKEY|ShiftMask,                             XK_d,                     setlayout,                     {.v = &layouts[5]} }, // deck
    { MODKEY,                                       XK_u,                     setlayout,                     {.v = &layouts[6]} }, // bstack
    { MODKEY|ShiftMask,                             XK_u,                     setlayout,                     {.v = &layouts[7]} }, // bstackhoriz
    { MODKEY|ShiftMask,                             XK_semicolon,             setlayout,                     {.v = &layouts[9]} }, // nrowgrid
    { MODKEY,                                       XK_p,                     setlayout,                     {.v = &layouts[12]} }, // centeredmaster
    { MODKEY|ShiftMask,                             XK_p,                     setlayout,                     {.v = &layouts[13]} }, // centeredfloatingmaster
    
    { MODKEY,                                       XK_space,                 setlayout,                     {0} },
    { MODKEY|ShiftMask,                             XK_space,                 togglefloating,                {0} },
    { MODKEY,                                       XK_Down,                  moveresize,                    {.v = "0x 25y 0w 0h" } },
    { MODKEY,                                       XK_Up,                    moveresize,                    {.v = "0x -25y 0w 0h" } },
    { MODKEY,                                       XK_Right,                 moveresize,                    {.v = "25x 0y 0w 0h" } },
    { MODKEY,                                       XK_Left,                  moveresize,                    {.v = "-25x 0y 0w 0h" } },
    { MODKEY|ShiftMask,                             XK_Down,                  moveresize,                    {.v = "0x 0y 0w 25h" } },
    { MODKEY|ShiftMask,                             XK_Up,                    moveresize,                    {.v = "0x 0y 0w -25h" } },
    { MODKEY|ShiftMask,                             XK_Right,                 moveresize,                    {.v = "0x 0y 25w 0h" } },
    { MODKEY|ShiftMask,                             XK_Left,                  moveresize,                    {.v = "0x 0y -25w 0h" } },
    { MODKEY,                                       XK_0,                     view,                          {.ui = ~0 } },
    { MODKEY|ShiftMask,                             XK_0,                     tag,                           {.ui = ~0 } },
    { MODKEY,                                       XK_comma,                 focusmon,                      {.i = -1 } },
    { MODKEY,                                       XK_period,                focusmon,                      {.i = +1 } },
    { MODKEY|ShiftMask,                             XK_comma,                 tagmon,                        {.i = -1 } },
    { MODKEY|ShiftMask,                             XK_period,                tagmon,                        {.i = +1 } },

    TAGKEYS(                                        XK_1,                                                     0)
    TAGKEYS(                                        XK_2,                                                     1)
    TAGKEYS(                                        XK_3,                                                     2)
    TAGKEYS(                                        XK_4,                                                     3)
    TAGKEYS(                                        XK_5,                                                     4)
    TAGKEYS(                                        XK_6,                                                     5)
    TAGKEYS(                                        XK_7,                                                     6)
    TAGKEYS(                                        XK_8,                                                     7)
    TAGKEYS(                                        XK_9,                                                     8)
  
  //{ MODKEY|ShiftMask,             XK_q,      quit,            {0} },
    { MODKEY|ShiftMask,             XK_q,      spawn,           SHCMD("loginctl -s 15 --no-ask-password terminate-session ${XDG_SESSION_ID}") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask               button          function               argument */
    { ClkLtSymbol,          0,                       Button1,        setlayout,             {0} },
    { ClkLtSymbol,          0,                       Button3,        setlayout,             {.v = &layouts[2]} },
    { ClkWinTitle,          0,                       Button2,        zoom,                  {0} },
    { ClkStatusText,        0,                       Button2,        spawn,                 {.v = termcmd } },
    
    { ClkStatusText,        0,                       Button1,        sigstatusbar,          {.i = 1} },
    { ClkStatusText,        0,                       Button2,        sigstatusbar,          {.i = 2} },
    { ClkStatusText,        0,                       Button3,        sigstatusbar,          {.i = 3} },
    { ClkStatusText,        0,                       Button4,        sigstatusbar,          {.i = 4} },
    { ClkStatusText,        0,                       Button5,        sigstatusbar,          {.i = 5} },
    
    { ClkClientWin,         MODKEY,                  Button1,        movemouse,             {0} },
    { ClkClientWin,         MODKEY,                  Button2,        togglefloating,        {0} },
    { ClkClientWin,         MODKEY|ShiftMask,        Button1,        resizemouse,           {0} },
    { ClkTagBar,            0,                       Button1,        view,                  {0} },
    { ClkTagBar,            0,                       Button3,        toggleview,            {0} },
    { ClkTagBar,            MODKEY,                  Button1,        tag,                   {0} },
    { ClkTagBar,            MODKEY,                  Button3,        toggletag,             {0} },
};

