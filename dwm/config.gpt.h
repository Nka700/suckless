static const Key keys[] = {
	/* modifier                     key                        function        argument */
	/* Volume keys */
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,          spawn,          {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = upvol   } },

	/* Brightness keys */
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          SHCMD("xbacklight +10") },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,          SHCMD("xbacklight -10") },

	/* Close window (Alt + F4) */
	{ Mod1Mask,                     XK_F4,                    killclient,     {0} },

	/* Screenshot (Print key) */
	{ 0,                            XK_Print,                 spawn,          SHCMD("sh -c 'xfce4-screenshooter -r -s ~/Downloads/Screenshot_$(date +%Y%m%d_%H%M%S).png'") },

	/* Show desktop (Super + d) */
	{ MODKEY,                       XK_d,                     toggleview,     {0} },

	/* Existing dwm keybindings */
	{ MODKEY,                       XK_p,                     spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,                spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                zoom,           {0} },
	{ MODKEY,                       XK_q,                     view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                     killclient,     {0} },
	{ MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                 setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
	{ MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
	{ Mod1Mask,                     XK_Tab,                   altTabStart,    {0} },
	{ MODKEY,                       XK_minus,                 setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,                 setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,                 setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                                     0)
	TAGKEYS(                        XK_2,                                     1)
	TAGKEYS(                        XK_3,                                     2)
	TAGKEYS(                        XK_4,                                     3)
	TAGKEYS(                        XK_5,                                     4)
	TAGKEYS(                        XK_6,                                     5)
	TAGKEYS(                        XK_7,                                     6)
	TAGKEYS(                        XK_8,                                     7)
	TAGKEYS(                        XK_9,                                     8)
	{ MODKEY|ShiftMask,             XK_q,                     quit,           {0} },
};

