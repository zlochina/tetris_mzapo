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

- **Any knob clockwise rotation**: go to the next option of the menu.
- **Any knob anti-clockwise rotation**: go to the previous option of the menu.
- **Any knob click**: choose the current option.

### Set Speed Controls

- **Any knob clockwise rotation**: increase the *speed* value.
- **Any knob anti-clockwise rotation**: decrease the *speed* value.
- **Any knob click**: set the *speed* value and exit the current state.

## Code Documentation

The code for the game is organized into the following files:
- `app_structure.h`: Defines enums including states of the application and game. Structure application_t of this file is used by most of the modules because it contains most of the temporary data of the application, including frame buffers to be written, metadata, game field data, and more. This helps in facilitating communication and data sharing between different parts of the game.
- `constants.h`:  This file contains strings to be displayed in both the terminal and the LCD display. It also contains colors that are shown on the LCD display, adding visual appeal to the game.
- `font_types.h`: Defines the different fonts used for text rendering.
- `game.c`: This file is mainly focused on rendering and beautifying functions. It includes functions responsible for updating the game state and rendering it on the screen. One of the most important functions in this file is update_state, which, based on the given flags, executes game actions accordingly. This file plays a vital role in ensuring the smooth flow and visual presentation of the game.
- `game_mechanics.c`: This file includes functions that update the state of the game. It handles crucial game mechanics such as clearing lines when they are fully filled, checking if the game or a particular figure can make a valid move, and more. The functions in this file ensure that the game behaves correctly and maintains its integrity throughout the gameplay.
- `figures.c`: Defines the different Tetris figures, including rotation states and colormap.
- `controllers.c`: Implements recognition of actions taken by knobs for the game.
- `lcd_chars.c`: Implements text rendering for the MZAPO device.
- `font_prop14x16.c`: Implements a 14x16 font.
- `font_rom8x16.c`: Implements an 8x16 font.
- `utils.c`: Implements utility functions used throughout the game.
- `mzapo_regs.h`: Defines the memory mapped IO register addresses for the MZAPO device.
- `mzapo_phys.c`: Provides the physical memory access for the MZAPO device.
- `serialize_lock.c`: Implements synchronization of access to shared resources.
- `menu.c`: This file includes functions responsible for handling the game menu. It manages the manipulations with both the LCD display and the LED line, providing an interactive and user-friendly interface. The functions in this file allow players to navigate through different options and settings in the game, enhancing the overall user experience.

The code is modular and organized to make it easier to understand and maintain.
Here's an updated version of the "Architecture Tree" section with the file dependencies:

## Architecture Tree
-**app_structure.h**  
---figures.h  
---constants.h  
---font_types.h  
-**constants.h**  
---utils.h  
-**controllers.c**  
---app_structure.h  
---constants.h  
---game_mechanics.h  
---menu.h  
---mzapo_regs.h  
---mzapo_phys.h  
---serialize_lock.h  
-**figures.c**  
---app_structure.h  
---constants.h  
---mzapo_regs.h  
---mzapo_phys.h  
-**font_prop14x16.c**  
-**font_rom8x16.c**  
-**font_types.h**  
-**game.c**  
---app_structure.h  
---constants.h  
---controllers.h  
---figures.h  
---game_mechanics.h  
---lcd_chars.h  
---mzapo_regs.h  
---mzapo_phys.h  
-**game_mechanics.c**  
---app_structure.h  
---constants.h  
---figures.h  
---mzapo_regs.h  
---mzapo_parlcd.h  
-**lcd_chars.h**  
---constants.h  
---font_types.h  
-**menu.c**  
---app_structure.h  
---constants.h  
---controllers.h  
---lcd_chars.h  
---mzapo_parlcd.h  
---mzapo_regs.h  
-**utils.c**

The above dependencies show which files are needed for each header file to function properly. It's important to note that some files may use absolute dependencies that are not listed here.

## Credits

The game was created by Vladyslav Zlochevskyi (zlochvla) as a semestral project for FEL CVUT. Special thanks to the creators of the MZAPO device for providing the necessary tools to create this game, including some of the mentioned files.
