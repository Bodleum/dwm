/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

#include <X11/XF86keysym.h>

/* appearance */
static const int startontag = 1;    /* 0 means no tag active on start */
static unsigned int borderpx = 1;   /* border pixel of windows */
static const int startwithgaps = 0; /* 1 means gaps are used by default */
static const unsigned int gappx =
    10;                        /* default gap between windows in pixels */
static unsigned int snap = 32; /* snap pixel */
static const int swallowfloating =
    0;                  /* 1 means swallow floating windows by default */
static int showbar = 1; /* 0 means no bar */
static int topbar = 1;  /* 0 means bottom bar */
static char font[] = "JetBrainsMono Nerd Font:size=14";
static char dmenufont[] = "JetBrainsMono Nerd Font:size=12";
static const char *fonts[] = {font};
static char col_white[] = "#fbf1c7";
static char col0[] = "#282828";
static char col1[] = "#cc241d";
static char col2[] = "#98971a";
static char col3[] = "#d79921";
static char col4[] = "#458588";
static char col5[] = "#b16286";
static char col6[] = "#689d6a";
static char col7[] = "#a89984";
static char col8[] = "#928374";
static char col9[] = "#fb4934";
static char col10[] = "#b8bb26";
static char col11[] = "#fabd2f";
static char col12[] = "#83a598";
static char col13[] = "#d3869b";
static char col14[] = "#8ec07c";
static char col15[] = "#ebdbb2";
static char col16[] = "#d65d0e";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [Schemecol0] = {col0, col0, col0},     [Schemecol1] = {col1, col0, col0},
    [Schemecol2] = {col2, col0, col0},     [Schemecol3] = {col3, col0, col0},
    [Schemecol4] = {col4, col0, col0},     [Schemecol5] = {col5, col0, col0},
    [Schemecol6] = {col6, col0, col0},     [Schemecol7] = {col7, col0, col0},
    [Schemecol8] = {col8, col0, col0},     [Schemecol9] = {col9, col0, col0},
    [Schemecol10] = {col10, col0, col0},   [Schemecol11] = {col11, col0, col0},
    [Schemecol12] = {col12, col0, col0},   [Schemecol13] = {col13, col0, col0},
    [Schemecol14] = {col14, col0, col0},   [Schemecol15] = {col15, col0, col0},
    [Schemecol16] = {col16, col0, col0},   [SchemeNorm] = {col7, col0, col0},
    [SchemeSel] = {col_white, col4, col4},
};

/* tagging */
static const char *tags[] = {"", "", "", "", "",
                             "", "", "", ""};
static const char *tagsalt[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
static const int momentaryalttags =
    0; /* 1 means alttags will show only when key is held down*/

static const unsigned int ulinepad =
    5; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke =
    2; /* thickness / height of the underline */
static const unsigned int ulinevoffset =
    0; /* how far above the bottom of the bar the line should appear */
static const int ulineall =
    0; /* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal
       noswallow  monitor */
    {"Alacritty", NULL, NULL, 0, 0, 1, 0, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1}, /* xev */
};

/* layout(s) */
static float mfact = 0.55;  /* factor of master area size [0.05..0.95] */
static int nmaster = 1;     /* number of clients in master area */
static int resizehints = 1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

#define TERMCMD(cmd)                                                           \
  {                                                                            \
    .v = (const char *[]) { "alacritty", "-e", cmd, NULL }                     \
  }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,       "-fn",
 */
/*                                  dmenufont,   "-nb", normbgcolor,    "-nf",
 */
/*                                  normfgcolor, "-sb", selbordercolor, "-sf",
 */
/*                                  selfgcolor,  NULL}; */
#define TERMINAL_ENVVAR "TERMINAL"

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    {"font", STRING, &font},          {"dmenufont", STRING, &dmenufont},
    {"borderpx", INTEGER, &borderpx}, {"snap", INTEGER, &snap},
    {"showbar", INTEGER, &showbar},   {"topbar", INTEGER, &topbar},
    {"nmaster", INTEGER, &nmaster},   {"resizehints", INTEGER, &resizehints},
    {"mfact", FLOAT, &mfact},         {"col_white", STRING, &col_white},
    {"col0", STRING, &col0},          {"col1", STRING, &col1},
    {"col2", STRING, &col2},          {"col3", STRING, &col3},
    {"col4", STRING, &col4},          {"col5", STRING, &col5},
    {"col6", STRING, &col6},          {"col7", STRING, &col7},
    {"col8", STRING, &col8},          {"col9", STRING, &col9},
    {"col10", STRING, &col10},        {"col11", STRING, &col11},
    {"col12", STRING, &col12},        {"col13", STRING, &col13},
    {"col14", STRING, &col14},        {"col15", STRING, &col15},
    {"col16", STRING, &col16},
};

static const Key keys[] = {
    /* modifier                     key        function        argument */

    // WM Actions
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_f, togglefullscr, {0}},
    {MODKEY, XK_g, setgaps, {.i = GAP_TOGGLE}},
    {MODKEY | ShiftMask, XK_g, setgaps, {.i = GAP_RESET}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_j, focusstack, {.i = INC(+1)}},
    {MODKEY, XK_k, focusstack, {.i = INC(-1)}},
    {MODKEY, XK_l, setmfact, {.f = 0.05}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_v, focusstack, {.i = 0}},
    {MODKEY, XK_x, setgaps, {.i = -5}},
    {MODKEY, XK_z, setgaps, {.i = +5}},
    {MODKEY, XK_space, zoom, {0}}, // Make current window master
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_Left, focusmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_Left, tagmon, {.i = -1}},
    {MODKEY, XK_Right, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_Right, tagmon, {.i = +1}},

    // Generic Bindings
    {MODKEY, XK_F4, spawn, TERMCMD("plusemixer")},
    {MODKEY, XK_F10, spawn, TERMCMD("dmenu_mount.sh")},
    {MODKEY, XK_F11, spawn, TERMCMD("dmenu_unmount.sh")},
    {MODKEY, XK_c, spawn, TERMCMD("calcurse")},
    {MODKEY, XK_e, spawn, TERMCMD("neomutt")},
    {MODKEY | ShiftMask, XK_e, spawn, TERMCMD("abook")},
    {MODKEY | ShiftMask, XK_f, spawn, SHCMD("ferdium")},
    {MODKEY, XK_m, spawn, TERMCMD("ncmpcpp")},
    {MODKEY | ShiftMask, XK_m, spawn, SHCMD("pamixer -t")},
    {MODKEY, XK_p, spawn, SHCMD("mpc toggle")},
    {MODKEY, XK_w, spawn, SHCMD("$BROWSER")},
    {MODKEY | ShiftMask, XK_w, spawn, TERMCMD("sudo nmtui")},
    {MODKEY, XK_BackSpace, spawn, TERMCMD("system_action.sh")},
    {MODKEY, XK_comma, spawn, SHCMD("mpc prev")},
    {MODKEY | ShiftMask, XK_comma, spawn, SHCMD("mpc seek 0%")},
    {MODKEY, XK_period, spawn, SHCMD("mpc next")},
    {MODKEY, XK_Return, spawn, SHCMD("alacritty")},
    {MODKEY, XK_Print, spawn, SHCMD("prtscr.sh")},
    {MODKEY | ShiftMask, XK_slash, spawn, TERMCMD("man bodleum-rice")},
    {Mod1Mask, XK_space, spawn, SHCMD("dmenu_run")},

    // Tags
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},

    // Debug
    {MODKEY, XK_d, dumpinfo, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
/* click                event mask      button          function argument */
#ifndef __OpenBSD__
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button1, sigstatusbar, {.i = 1}},
    {ClkStatusText, 0, Button2, sigstatusbar, {.i = 2}},
    {ClkStatusText, 0, Button3, sigstatusbar, {.i = 3}},
    {ClkStatusText, 0, Button4, sigstatusbar, {.i = 4}},
    {ClkStatusText, 0, Button5, sigstatusbar, {.i = 5}},
    {ClkStatusText, ShiftMask, Button1, sigstatusbar, {.i = 6}},
    {ClkStatusText, ShiftMask, Button2, sigstatusbar, {.i = 7}},
    {ClkStatusText, ShiftMask, Button3, sigstatusbar, {.i = 8}},
    {ClkStatusText, ShiftMask, Button4, sigstatusbar, {.i = 9}},
    {ClkStatusText, ShiftMask, Button5, sigstatusbar, {.i = 10}},
#endif
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, setgaps, {.i = GAP_RESET}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkClientWin, MODKEY, Button4, setgaps, {.i = +1}},
    {ClkClientWin, MODKEY, Button5, setgaps, {.i = -1}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

void setlayoutex(const Arg *arg) { setlayout(&((Arg){.v = &layouts[arg->i]})); }

void viewex(const Arg *arg) { view(&((Arg){.ui = 1 << arg->ui})); }

void viewall(const Arg *arg) { view(&((Arg){.ui = ~0})); }

void toggleviewex(const Arg *arg) { toggleview(&((Arg){.ui = 1 << arg->ui})); }

void tagex(const Arg *arg) { tag(&((Arg){.ui = 1 << arg->ui})); }

void toggletagex(const Arg *arg) { toggletag(&((Arg){.ui = 1 << arg->ui})); }

void tagall(const Arg *arg) { tag(&((Arg){.ui = ~0})); }

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"`
 */
static Signal signals[] = {
    /* signum           function */
    {"focusstack", focusstack},
    {"setmfact", setmfact},
    {"togglebar", togglebar},
    {"incnmaster", incnmaster},
    {"togglefloating", togglefloating},
    {"focusmon", focusmon},
    {"tagmon", tagmon},
    {"zoom", zoom},
    {"view", view},
    {"viewall", viewall},
    {"viewex", viewex},
    {"toggleview", view},
    {"toggleviewex", toggleviewex},
    {"tag", tag},
    {"tagall", tagall},
    {"tagex", tagex},
    {"toggletag", tag},
    {"toggletagex", toggletagex},
    {"killclient", killclient},
    {"quit", quit},
    {"setlayout", setlayout},
    {"setlayoutex", setlayoutex},
    {"dumpinfo", dumpinfo},
};