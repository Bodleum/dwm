/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"      // sh command to open the terminal

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
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
#define MODKEY Mod4Mask     // Windows key
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

static Key keys[] = {
    /* modifier                     key             function        argument */
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
    { MODKEY,                       XK_e,           spawn,          SHCMD(TERMINAL " -e mailsync && neomutt") },    // Sync email and open neomutt. TODO: Signal dwmblocks to update email.
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
    //{ MODKEY,                       XK_bracketright, spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_bracketright, spawn,          SHCMD("") },

    //{ MODKEY,                       XK_a,           spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_a,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_s,           spawn,          SHCMD("") },    // Make window sticky
    //{ MODKEY|ShiftMask,             XK_s,           spawn,          SHCMD("") },
    { MODKEY,                       XK_d,           spawn,          SHCMD("dmenu_run") },   // Launch a program, try and change to just MOD
    //{ MODKEY|ShiftMask,             XK_d,           spawn,          SHCMD("") },
    { MODKEY,                       XK_f,           spawn,          SHCMD(TERMINAL " -e ferdi") },  // Launch ferdi
    //{ MODKEY|ShiftMask,             XK_f,           togglefullscr,  {0} },  // Toggle full screen
    //{ MODKEY,                       XK_g,           togglegaps,     {0} },  // Toggle gaps
    //{ MODKEY|ShiftMask,             XK_g,           defaultgaps,    {0} },  // Reset gaps to default
    { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} }, // Reduce size of master window
    //{ MODKEY|ShiftMask,             XK_h,           spawn,          SHCMD("") },
    /*
        J and K are bound in STACKKEYS
    */
    { MODKEY,                       XK_l,           setmfact,       {.f = 0.05} },  // Increase size of master window
    //{ MODKEY|ShiftMask,             XK_l,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_semicolon,   spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_semicolon,   spawn,          SHCMD("") },
    //{ MODKEY,                       XK_apostrophe,  spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_apostrophe,  spawn,          SHCMD("") },
    //{ MODKEY,                       XK_backslash,   spawn,          SHCMD("") },
    //{ MODKEY|ShiftMask,             XK_backslash,   spawn,          SHCMD("") },

    //{ MODKEY,                       XK_z,           incrgaps,       {.i = +3} },    // Increase gaps
    //{ MODKEY|ShiftMask,             XK_z,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_x,           incrgaps        {.i = -3} },    // Decrease gaps
    //{ MODKEY|ShiftMask,             XK_x,           spawn,          SHCMD("") },
    //{ MODKEY,                       XK_c,           spawn,          SHCMD("") },
    { MODKEY|ShiftMask,             XK_c,           spawn,          SHCMD("mpv --no-cache --no-osc --on-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=Webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },    // Open webcam
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

    { MODKEY,                       XK_Return,      spawn,          {.v = termcmd} },   // Open terminal
    //{ MODKEY|ShiftMask,             XK_Return,      spawn,          SHCMD("") },    // Floating terminal
    //{ MODKEY,                       XK_Insert,      spawn,          SHCMD("") },    // Select from clipboard
    { 0,                            XK_Print,       spawn,          SHCMD("prtscr.sh") },   // Print screen dmenu prompt

    { MODKEY,                       XK_Left,        focusmon,       {.i = -1 } },   // Focus on monitor to the left
    { MODKEY|ShiftMask,             XK_Left,        tagmon,         {.i = -1 } },   // Move window to monitor to the left
    { MODKEY,                       XK_Right,       focusmon,       {.i = +1 } },   // Focus on monitor to the right
    { MODKEY|ShiftMask,             XK_Right,       tagmon,         {.i = +1 } },   // Move window to monitor to the right
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

