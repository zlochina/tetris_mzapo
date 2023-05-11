# Tetris Game for MZAPO

This is a Tetris game written in C language for MZAPO.

## Installation

To install and run the game, follow these steps:

1. Clone the repository to node connected to inner network of FEL:

```
git clone https://gitlab.fel.cvut.cz/B222_B0B35APO/zlochvla
```

2. Navigate to the `zlochvla` directory:

```
cd zlochvla
```

3. Compile the game using the following command:

```
make
```

4. Run the game with the following command (Replace "xxx" with actual IP of MZAPO device):

```
make TARGET_IP=192.168.223.xxx run
```

## User Manual

### Controls

- **Top knob clockwise rotation**: rotate the falling block clockwise.
- **Top knob anti-clockwise rotation**: rotate the falling block anti-clockwise.
- **Central knob clockwise rotation**: move the falling block to the right.
- **Central knob anti-clockwise rotation**: move the falling block to the left.
- **Bottom knob clockwise rotation**: move the falling block faster.
- **Top knob click or Bottom knob click**: pause the game.
- **Central knob click**: drop the falling block instantly.

### Menu Controls

- **Any knob clockwise rotation: go to the next option of the menu.
- **Any knob anti-clockwise rotation: go to the previous option of the menu.
- **Any knob click: choose the current option.

### Set Speed Controls

- **Any knob clockwise rotation**: increase the *speed* value.
- **Any knob anti-clockwise rotation**: decrease the *speed* value.
- **Any knob click**: set the *speed* value and exit the current state.

## Code Documentation

The code for the game is organized into the following files:

- `app_structure.h`: Defines the main data structures used by the game.
- `constants.h`: Defines the constant values used throughout the game.
- `font_types.h`: Defines the different fonts used for text rendering.
- `game.c`: Implements the main logic for the game.
- `game_mechanics.c`: Implements the game mechanics and figures rendering.
- `figures.c`: Defines the different Tetris figures, including rotation states and colormap.
- `controllers.c`: Implements recognition of actions taken by knobs for the game.
- `lcd_chars.c`: Implements text rendering for the MZAPO device.
- `font_prop14x16.c`: Implements a 14x16 font.
- `font_rom8x16.c`: Implements an 8x16 font.
- `utils.c`: Implements utility functions used throughout the game.
- `mzapo_regs.h`: Defines the memory mapped IO register addresses for the MZAPO device.
- `mzapo_phys.c`: Provides the physical memory access for the MZAPO device.
- `serialize_lock.c`: Implements synchronization of access to shared resources.
- `menu.c`: Implements the game menu and set speed mode.

The code is modular and organized to make it easier to understand and maintain.

## Credits

The game was created by Vladyslav Zlochevskyi (zlochvla) as a semestral project for FEL CVUT. Special thanks to the creators of the MZAPO device for providing the necessary tools to create this game, including some of the mentioned files.
