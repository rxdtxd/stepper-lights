# stepper-lights

## Table of Contents

* [Intro](#intro)
* [Using](#using)
  - [Warning](#warning)
  - [Overview](#overview)
  - [Schematics](#schematics)
  - [BOM](#bom)
  - [Fabrication files](#fabrication-files)
* [Modifying](#modifying)
  - [Toolchain](#toolchain)
  - [Custom symbols/footprints](#custom-symbolsfootprints)
* [Notes](#notes)
* [License](#license)


## Intro

Here's a project I did in early 2016 on controlling five stepper
motors with one AVR (Arduino Nano). Each channel has up/down
buttons and a potentiometer to control the speed.


## Using

### Warning

**I strongly suggest you do not try to recreate it verbatim, and use
as a guide at best.**

The schematics/layouts contained numerous glitches and therefore
impromptu fixes that were not propagated back to the design files.

Most notably, the used Arduino Nano symbol had its ADC pin order
reversed on the manufactured boards ([rev0.1](releases/tag/rev0.1)).
This required both hardware jumpering and software muckery, somewhat
reflected in [rev0.2](releases/tag/rev0.2).

Furthermore, the overall design leaves much to be desired. With
the current prices for Arduino Nano clones, **this should have been
a one-AVR-one-driver schematic**.

However, in the spirit of megalomania, I hereby release the files
under free licenses (for which see the bottom).


### Overview

There are two parts to the system: `controller` and `driver`:

```
             +-> driver
             |
             +-> driver
             |
controller --+-> driver
             |
             +-> driver
             |
             +-> driver
```

Communication is essentially single-directional SPI over RS422,
with the driver transmitting back a dummy message (i.e. no
feedback).


### Schematics

See [controller.png](schem/controller.png) and
[driver.png](schem/driver.png).


### BOM

See [controller.bom](schem/controller.bom) and
[driver.bom](schem/driver.bom).

Some mechanical components are not listed:

* push-buttons (OFF-(ON))
* power supply (24 V, 2+ A)
* power switch (OFF-ON)
* cooling fans (24 V)
* CAT6 cables and RJ45 connectors


### Fabrication files

See [fab](schem/fab) for gerbers and drill maps.


## Modifying

### Toolchain

The design files were produced on a [Arch](https://www.archlinux.org/)
GNU/Linux machine using [geda/gaf](http://www.geda-project.org/),
[pcb](http://pcb.geda-project.org/) and
[Emacs](https://www.gnu.org/software/emacs/).

AVR sources are built with [avr-gcc](https://gcc.gnu.org/). Arduino
is flashed with [avrdude](http://www.nongnu.org/avrdude/).

There are Makefiles for both schematics and code. Happy hacking!


### Custom symbols/footprints

...used in this project are available in my
[symbols](https://github.com/rxdtxd/geda-gschem-symbols-rxdtxd) and
[footprints](https://github.com/rxdtxd/geda-pcb-footprints-rxdtxd)
repos.

Note that these may have changed from the time they were used in the
project. I hope I was decent enough to change `symver`s and whatnot if
so.

## Notes

Some more unordered documentation is available in the [NOTES](NOTES)
file.


## License

Software in [src](src/) is licensed under [GPLv3](src/LICENSE). Hardware
designs in [schem](schem/) are licensed under [CERN OHL
v1.2](schem/LICENSE).
