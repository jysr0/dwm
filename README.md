# dwm-6.6 build
![](dwm-6.6.png)
## INSTALATION
1. make sure `xorg-xinit' is installed, if not, install it based on your distro's package manager.
2. append `exec startx dwm' at end of your bash_profile.
3. clone the repo, (git clone https://github.com/jysr0/dwm-6.6 && cd dwm-6.6).
4. IMPORTANT: configure config.def.h before continuing e.g. terminal and dmenu/rofi, or you'll get stuck.
5. sudo make clean install
6. reboot
### dwmblocks-async
Install and configure [dwmblocks-async](https://github.com/UtkarshVerma/dwmblocks-async) with some scripts, and that's it.
If some issues happen with the clicking see [issues](https://github.com/UtkarshVerma/dwmblocks-async/issues).
## KEY BINDS
Look for config.def.h's keys array.
## PATCHES
[vanitygaps](https://dwm.suckless.org/patches/vanitygaps/), the one that includes most layouts.  <br />
[awesomebar](https://dwm.suckless.org/patches/awesomebar/).  <br />
[alpha](https://dwm.suckless.org/patches/alpha/), the "fixborders" one.  <br />
[hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/).  <br />
[pertag](https://dwm.suckless.org/patches/pertag/).  <br />
[attachdirection](https://dwm.suckless.org/patches/attachdirection/).  <br />
[movestack](https://dwm.suckless.org/patches/movestack/).  <br />
[switchcol](https://dwm.suckless.org/patches/switchcol/).  <br />
[decoration hints](https://dwm.suckless.org/patches/decoration_hints/).  <br />
[moveresize](https://dwm.suckless.org/patches/moveresize/).  <br />
[statuscmd](https://dwm.suckless.org/patches/statuscmd/), "with signals" one.  <br />
[zoomswap](https://dwm.suckless.org/patches/zoomswap/).  <br />
[bulkill](https://dwm.suckless.org/patches/bulkill/), the "safe" one.  <br />
[tiledmove](https://dwm.suckless.org/patches/tiledmove/).  <br />
[togglefloatingcenter](https://dwm.suckless.org/patches/togglefloatingcenter/).  <br />
[shift tools](https://dwm.suckless.org/patches/shift-tools/), the "\*.c" one.  <br />
[alwayscenter](https://dwm.suckless.org/patches/alwayscenter/).  <br />
[allowkillrule](https://dwm.suckless.org/patches/allowkillrule/).  <br />
[pwkl](https://dwm.suckless.org/patches/pwkl/).  <br />
[inplacerotate](https://dwm.suckless.org/patches/inplacerotate/).  <br />
[center](https://dwm.suckless.org/patches/center/).  <br />
[sticky](https://dwm.suckless.org/patches/sticky/).  <br />
## LAYOUT PATCHES
[nrowgrid](https://dwm.suckless.org/patches/nrowgrid/).  <br />
[gaplessgrid](https://dwm.suckless.org/patches/gaplessgrid/).  <br />
[fibonacci](https://dwm.suckless.org/patches/fibonacci/).  <br />
[deck](https://dwm.suckless.org/patches/deck/).  <br />
[bottomstack](https://dwm.suckless.org/patches/bottomstack/).  <br />
[centeredmaster](https://dwm.suckless.org/patches/centeredmaster/).
