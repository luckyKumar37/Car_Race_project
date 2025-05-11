# Galactic Recoil

A 2D top-down shooting adventure game made using C++ and SFML (Simple and Fast Multimedia Library). You play as a space survivor in an alien-infested terrain, dodging enemies, shooting down threats, and staying alive as long as you can!

## 🛠 How It's Made
- **Language**: C++
- **Library**: SFML (Graphics, Audio, and Input handling)

## Game Components:
- **Player**: Moves with WASD, shoots toward mouse direction.
- **Enemies**: Spawn randomly and chase the player.
- **Bullets**: Fired from the player toward mouse position.
- **Health System**: Health decreases on enemy contact and regenerates over time.
- **Score System**: Score increases with every enemy killed.
- **Health Bar**: Displays current health with label.
- **Time Trial Mode**: Complete objectives within a time limit (kill a specific number of enemies).
- **Difficulty Scaling**: Enemies spawn more frequently and in larger numbers as the game progresses.
- **Collision System**: Enemies bounce back when colliding with the player.
- **Audio System**: Background music and sound effects for actions like shooting.
- **Intro and Game Over Screens**: User can start or restart the game with buttons.

## 🎮 Controls
- **W/A/S/D** – Move up/left/down/right
- **Left Mouse Click** – Fire bullet in the direction of the mouse
- **Mouse** – Aim

## Game Modes
- **Standard Mode**: Survive as long as possible while defeating enemies.
- **Time Trial**: Kill a specified number of enemies (default: 50) within a time limit (default: 60 seconds).
