/* See LICENSE file for copyright and license details. */

#define TERMINAL "alacritty"      // sh command to open the terminal
#define TERMCLASS "Alacritty"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=14", "NotoColorEmoji:antialias=true:autohint=true:pixelsize=20", "JoyPixels:pixelsize=20:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_white[]       = "#fbf1c7";
static const char col0[]            = "#282828";
static const char col1[]            = "#cc241d";
static const char col2[]            = "#98971a";
static const char col3[]            = "#d79921";
static const char col4[]            = "#458588";
static const char col5[]            = "#b16286";
static const char col6[]            = "#689d6a";
static const char col7[]            = "#a89984";

static const char col8[]            = "#928374";
static const char col9[]            = "#fb4934";
static const char col10[]           = "#b8bb26";
static const char col11[]           = "#fabd2f";
static const char col12[]           = "#83a598";
static const char col13[]           = "#d3869b";
static const char col14[]           = "#8ec07c";
static const char col15[]           = "#ebdbb2";
static const char col16[]           = "#d65d0e";

enum {  SchemeCol0,
        SchemeCol1,
        SchemeCol2,
        SchemeCol3,
        SchemeCol4,
        SchemeCol5,
        SchemeCol6,
        SchemeCol7,
        SchemeCol8,
        SchemeCol9,
        SchemeCol10,
        SchemeCol11,
        SchemeCol12,
        SchemeCol13,
        SchemeCol14,
        SchemeCol15,
        SchemeCol16,
        SchemeNorm,
        SchemeWinSel,
        SchemeBar
}; /* color schemes */

static const char *colors[][3]      = {
    /*                  fg         bg       border   */
    [SchemeCol0]    = { col0,      col0,    col0 },
    [SchemeCol1]    = { col1,      col0,    col0 },
    [SchemeCol2]    = { col2,      col0,    col0 },
    [SchemeCol3]    = { col3,      col0,    col0 },
    [SchemeCol4]    = { col4,      col0,    col0 },
    [SchemeCol5]    = { col5,      col0,    col0 },
    [SchemeCol6]    = { col6,      col0,    col0 },
    [SchemeCol7]    = { col7,      col0,    col0 },
    [SchemeCol8]    = { col8,      col0,    col0 },
    [SchemeCol9]    = { col9,      col0,    col0 },
    [SchemeCol10]   = { col10,     col0,    col0 },
    [SchemeCol11]   = { col11,     col0,    col0 },
    [SchemeCol12]   = { col12,     col0,    col0 },
    [SchemeCol13]   = { col13,     col0,    col0 },
    [SchemeCol14]   = { col14,     col0,    col0 },
    [SchemeCol15]   = { col15,     col0,    col0 },
    [SchemeCol16]   = { col16,     col0,    col0 },
    [SchemeNorm]    = { col_white, col0,    col0 },
    [SchemeWinSel]  = { col_white, col2,    col2 },
    [SchemeBar]     = { col_white, col4,    col4 },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
/* st version */
//const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
//const char *spcmd2[] = { TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
/* Alacritty version */
const char *spcmd1[] = { TERMINAL, NULL };
const char *spcmd2[] = { TERMINAL, "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
    {"spcalc",      spcmd2},
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const unsigned int ulinepad  = 5;    /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke   = 2;    /* thickness / height of the underline */
static const unsigned int ulinevoffset  = 0;    /* how far above the bottom of the bar the line should appear */
static const int ulineall       = 0;    /* 1 to show underline on all tags, 0 for just the active ones */

static const char ptagf[] = "%s";  /* format of a tag label */
static const char etagf[] = "%s"; /* format of an empty tag */
static const int lcaselbl = 0;      /* 1 means make tag label lowercase */

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { TERMCLASS, NULL,     NULL,           0,         0,          1,           0,        -1 },
    { NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
    { NULL,      "spterm", NULL,           SPTAG(0),  1,          1,           0,        -1 },
    { NULL,      "spcalc", NULL,           SPTAG(1),  1,          1,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
    { "H[]",      deck },
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
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
    { MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
    { MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
    { MOD, XK_v,     ACTION##stack, {.i = 0} }, \
    //{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
    //{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
    //{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
    //{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
    //{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                     key             function        argument */
    STACKKEYS(MODKEY,                               focus)
    STACKKEYS(MODKEY|ShiftMask,                     push)

    //{ MODKEY,                       XK_escape,      spawn,          SHCMD("") },
    //{ MODKEY,                       XK_F1,          spawn,          SHCMD("") },
    //{ MODKEY,                       XK_F2,          spawn,          SHCMD("") },
    //{ MODKEY,                       XK_F3,          spawn,          SHCMD("") },
    { MODKEY,                       XK_F4,          spawn,          SHCMD(TERMINAL " -e pulsemixer") }, // Open plusemixer for audio control. TODO: Signal dwmblocks to update.
    //{ MODKEY,                       XK_F5,          spawn,          SHCMD("") },
    //{ MODKEY,                       XK_F6,          spawn,          SHCMD("") },
    //{ MODKEY,                       XK_F7,          spawn,          SHCMD("") },
    //{ MODKEY,                       XK_F8,          spawn,          SHCMD("") },
    //{ MODKEY,                       XK_F9,          spawn,          SHCMD("") },
    { MODKEY,                       XK_F10,         spawn,          SHCMD("dmenu_mount.sh") },  // Mount drives
    { MODKEY,                       XK_F11,         spawn,          SHCMD("dmenu_unmount.sh") },    // Unmount drives
    //{ MODKEY,                       XK_F12,         spawn,          SHCMD("") },

    //{ MODKEY,                       XK_grave,       spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_grave,       spawn,          SHCMD("") },
    TAGKEYS(                        XK_1,                           0)
    TAGKEYS(                        XK_2,                           1)
    TAGKEYS(                        XK_3,                           2)
    TAGKEYS(                        XK_4,                           3)
    TAGKEYS(                        XK_5,                           4)
    TAGKEYS(                        XK_6,                           5)
    TAGKEYS(                        XK_7,                           6)
    TAGKEYS(                        XK_8,                           7)
    TAGKEYS(                        XK_9,                           8)
    { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
    //{ MODKEY,                       XK_minus,       spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_minus,       spawn,          SHCMD("") },
    //{ MODKEY,                       XK_equal,       spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_equal,       spawn,          SHCMD("") },
    { MODKEY,                       XK_BackSpace,   spawn,          SHCMD("system_action.sh") },    // System action
    { MODKEY|ShiftMask,             XK_BackSpace,   spawn,          SHCMD("system_action.sh") },    // System action

    //{ MODKEY,                       XK_Tab,         spawn,          SHCMD("") },
    { MODKEY,                       XK_q,           killclient,     {0} },   // Close current window
    //{ MODKEY|ShiftMask,             XK_q,           spawn,          SHCMD("") },
    { MODKEY,                       XK_w,           spawn,          SHCMD("$BROWSER") }, // Open web browser
    { MODKEY|ShiftMask,             XK_w,           spawn,          SHCMD(TERMINAL " -e sudo nmtui") }, // nmtui for network configuration
    { MODKEY,                       XK_e,           spawn,          SHCMD(TERMINAL " -e neomutt") },    // Sync email and open neomutt. TODO: Signal dwmblocks to update email.
    { MODKEY|ShiftMask,             XK_e,           spawn,          SHCMD(TERMINAL " -e abook") },  // Open abook
    //{ MODKEY,                       XK_r,           spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_r,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_t,           spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_t,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_y,           spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_y,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_u,           spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_u,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_i,           spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_i,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_o,           spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_o,           spawn,          SHCMD("") },
    { MODKEY,                       XK_p,           spawn,          SHCMD("mpc toggle") },  // play/pause mpd
    //{ MODKEY|ShiftMask,             XK_p,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_bracketleft, spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_bracketleft, spawn,          SHCMD("") },
    //{ MODKEY,                       XK_bracketright,spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_bracketright,spawn,          SHCMD("") },

    //{ MODKEY,                       XK_a,           spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_a,           spawn,          SHAMED("") },
    { MODKEY,                       XK_s,           togglesticky,     {0} },    // Make window sticky
    //{ MODKEY|ShiftMask,             XK_s,           spawn,          SHCMD("") },
    { MODKEY,                       XK_d,           spawn,          SHCMD("dmenu_run") },   // Launch a program, try and change to just MOD
    //{ MODKEY|ShiftMask,             XK_d,           spawn,          SHCMD("") },
    { MODKEY,                       XK_f,           spawn,          SHCMD(TERMINAL " -e ferdi") },  // Launch ferdi
    { MODKEY|ShiftMask,             XK_f,           togglefullscr,  {0} },  // Toggle full screen
    { MODKEY,                       XK_g,           togglegaps,     {0} },  // Toggle gaps
    { MODKEY|ShiftMask,             XK_g,           defaultgaps,    {0} },  // Reset gaps to default
    { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} }, // Reduce size of master window
    //{ MODKEY|ShiftMask,             XK_h,           spawn,          SHCMD("") },
    /*
        J and K are bound in STACKKEYS
    */
    { MODKEY,                       XK_l,           setmfact,       {.f = 0.05} },  // Increase size of master window
    //{ MODKEY|ShiftMask,             XK_l,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_semicolon,   spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_semicolon,   spawn,          SHCMD("") },
    { MODKEY,                       XK_apostrophe,  togglescratch,  {.ui = 1} },    // Open calculator
    //{ MODKEY|ShiftMask,             XK_apostrophe,  spawn,          SHCMD("") },
    //{ MODKEY,                       XK_backslash,   spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_backslash,   spawn,          SHCMD("") },

    { MODKEY,                       XK_z,           incrgaps,       {.i = +3} },    // Increase gaps
    //{ MODKEY|ShiftMask,             XK_z,           spawn,          SHCMD("") },
    { MODKEY,                       XK_x,           incrgaps,       {.i = -3} },    // Decrease gaps
    //{ MODKEY|ShiftMask,             XK_x,           spawn,          SHCMD("") },
    { MODKEY,                       XK_c,           spawn,          SHCMD(TERMINAL " -e calcurse") },   // Open Calendar
    { MODKEY|ShiftMask,             XK_c,           spawn,          SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=Webcam $(/bin/ls /dev/video[0,2,4,6,8] | tail -n 1)") },    // Open webcam
    /*
        V is bound in STACKKEYS
    */
    { MODKEY,                       XK_b,           togglebar,      {0} },  // Toggle status bar
    //{ MODKEY|ShiftMask,             XK_b,           spawn,          SHCMD("") },
    { MODKEY,                       XK_n,           spawn,          SHCMD(TERMINAL " -e nvim -c VimwikiIndex") },   // Open Vimwiki
    //{ MODKEY|ShiftMask,             XK_n,           spawn,          SHCMD("") },
    { MODKEY,                       XK_m,           spawn,          SHCMD(TERMINAL " -e ncmpcpp") },    // Open ncmpcpp
    { MODKEY|ShiftMask,             XK_m,           spawn,          SHCMD("pamixer -t") },  // Toggle mute. TODO: Signal dwmblocks to update
    { MODKEY,                       XK_comma,       spawn,          SHCMD("mpc prev") },    // Previous song
    { MODKEY|ShiftMask,             XK_comma,       spawn,          SHCMD("mpc seek 0%") }, // Go to start of song
    { MODKEY,                       XK_period,      spawn,          SHCMD("mpc next") },    // Next song
    //{ MODKEY|ShiftMask,             XK_period,      spawn,          SHCMD("") },

    { MODKEY,                       XK_space,       zoom,           {0} },  // Make current window master
    { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },  // Toggle floating
    { Mod1Mask,                     XK_space,       spawn,          SHCMD("dmenu_run") },  // Launch a program

    { MODKEY,                       XK_Return,      spawn,          {.v = termcmd} },   // Open terminal
    { MODKEY|ShiftMask,             XK_Return,      togglescratch,  {.ui = 0} },    // Floating terminal
    //{ MODKEY,                       XK_Insert,      spawn,          SHCMD("") },    // Select from clipboard
    { 0,                            XK_Print,       spawn,          SHCMD("prtscr.sh") },   // Print screen dmenu prompt

    { MODKEY,                       XK_Left,        focusmon,       {.i = -1 } },   // Focus on monitor to the left
    { MODKEY|ShiftMask,             XK_Left,        tagmon,         {.i = -1 } },   // Move window to monitor to the left
    { MODKEY,                       XK_Right,       focusmon,       {.i = +1 } },   // Focus on monitor to the right
    { MODKEY|ShiftMask,             XK_Right,       tagmon,         {.i = +1 } },   // Move window to monitor to the right


    { 0, XF86XK_AudioMute,          spawn,                          SHCMD("pamixer -t; kill -39 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioRaiseVolume,   spawn,                          SHCMD("pamixer --allow-boost -i 3; kill -39 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioLowerVolume,   spawn,                          SHCMD("pamixer --allow-boost -d 3; kill -39 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioPrev,          spawn,                          SHCMD("mpc prev") },
    { 0, XF86XK_AudioNext,          spawn,                          SHCMD("mpc next") },
    { 0, XF86XK_AudioPause,         spawn,                          SHCMD("mpc pause") },
    { 0, XF86XK_AudioPlay,          spawn,                          SHCMD("mpc play") },
    { 0, XF86XK_AudioStop,          spawn,                          SHCMD("mpc stop") },
    { 0, XF86XK_AudioRewind,        spawn,                          SHCMD("mpc seek -10") },
    { 0, XF86XK_AudioForward,       spawn,                          SHCMD("mpc seek +10") },
    { 0, XF86XK_AudioMedia,         spawn,                          SHCMD(TERMINAL " -e ncmpcpp") },
    { 0, XF86XK_AudioMicMute,       spawn,                          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
    { 0, XF86XK_PowerOff,           spawn,                          SHCMD("system_action.sh") },
    { 0, XF86XK_Calculator,         spawn,                          SHCMD(TERMINAL " -e bc -l") },
    { 0, XF86XK_Sleep,              spawn,                          SHCMD("system_action.sh") },
    { 0, XF86XK_WWW,                spawn,                          SHCMD("$BROWSER") },
    { 0, XF86XK_DOS,                spawn,                          SHCMD(TERMINAL) },
    { 0, XF86XK_ScreenSaver,        spawn,                          SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
    { 0, XF86XK_TaskPane,           spawn,                          SHCMD(TERMINAL " -e bpytop") },
    { 0, XF86XK_Mail,               spawn,                          SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+3 dwmblocks") },
    { 0, XF86XK_MyComputer,         spawn,                          SHCMD(TERMINAL " -e lf /") },
    { 0, XF86XK_Battery,            spawn,                          SHCMD("") },
    { 0, XF86XK_Launch1,            spawn,                          SHCMD("xset dpms force off") },
    { 0, XF86XK_TouchpadToggle,     spawn,                          SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOff,        spawn,                          SHCMD("synclient TouchpadOff=1") },
    { 0, XF86XK_TouchpadOn,         spawn,                          SHCMD("synclient TouchpadOff=0") },
    { 0, XF86XK_MonBrightnessUp,    spawn,                          SHCMD("xbacklight -inc 15") },
    { 0, XF86XK_MonBrightnessDown,  spawn,                          SHCMD("xbacklight -dec 15") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
#ifndef __OpenBSD__
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
    { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
    { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
    { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
    { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
    { ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
    { ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        defaultgaps,    {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkClientWin,         MODKEY,         Button4,        incrgaps,       {.i = +1} },
    { ClkClientWin,         MODKEY,         Button5,        incrgaps,       {.i = -1} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

