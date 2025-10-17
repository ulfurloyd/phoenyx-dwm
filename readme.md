<h2 align="center">phoenyx-dwm </h2>

<h2 align="center">
    <img src="./.github/ulfurloyd.jpg" width="240" alt="ulfurloyd" />
</h2>

![wolf-dwm](./.github/screenshot.png)

## my build of dwm, the tiling wm that sucks less
- `dwm` is an elegant, minimalist, enthusiast x11 window manager that sucks less.
- configured entirely through modifying the source code, `dwm` is a blast to sift through, and teaches you tons about `c`.

## patches
- cool_autostart
    - implements autostart functionality controllable through `config.def.h`
- fullgaps
    - adds controllable gaps between windows
- bar-height-spacing
    - lets you set the height of the bar
- statusallmons
    - shows the status portion of the bar on all outputs instead of only the focused one
- windowfollow
    - makes focus follow a window that's been sent to a different tag
- focusmonmouse
    - makes the mouse pointer follow focus change to a different output
- actualfullscsreen
    - changes fullscreen behaviour into actual fullscreen instead of bartoggle+monocle

## statusbar
- standard `dwm` bar
- using `dwmblocks-async` for status information
