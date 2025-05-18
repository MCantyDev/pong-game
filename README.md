# Pong

## Overview

A simple Pong game created with **SFML**. The game supports **Player vs AI**, **Player vs Player (Local Multiplayer)**, with engaging music and sound effects.

---

> **Note** - This project is primarily a University Assignment

### Features

- Player vs AI
- Player vs Player (Local Multiplayer on the same computer)
- Background music and sound effects


### Future Plans

- Online Player vs Player

### File Structure

- libraries/: External libraries used throughout the project
- project/: Root directory of the project
  - assets/: Assets such as fonts, music, and sound effects
  - include/: All header files
  - src/: Source files
    - command/: Command Pattern implementation files
    - core/: Core functionality of the application
    - drawables/: Drawable objects to be rendered on screen
    - factory/: Factory Pattern implementation files
    - observer/: Observer Pattern implementation files
    - state/: Game states and state management

### Technologies Used

- **CMake** – Cross-platform build system to manage compilation and dependencies.
- **SFML (Simple and Fast Multimedia Library)** – Handles rendering, window management, input, audio, and networking.
- **OpenGL** – Graphics API leveraged by SFML for rendering.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/MCantyDev/pong-game.git
   ```

2. Create the build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Run CMake:
   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release
   cmake --build . --config Release
   ```

4. Run Application:
   ```bash
   // Go to bin folder
   // Double click PongGame.exe
   ```


### Licensing

This project is licensed under the MIT License - See the LICENSE file for details.

---
