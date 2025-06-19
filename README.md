# 🧱 Cube3D

A minimalist 3D raycasting engine built entirely in C, inspired by the classic game **Wolfenstein 3D**.  
Created as part of the 42 coding school's "Cub3D" project to deepen understanding of graphics programming, mathematical modeling, and low-level rendering.

## 🚀 Features

- 🔭 **Raycasting Engine** (built from scratch)
- 🧭 First-person view with real-time movement and rotation
- 🧱 Wall and floor rendering with texture mapping
- 👣 WASD-based player movement with collision detection
- 🗺️ Custom map parsing from `.cub` files
- 📐 Realistic field of view simulation using trigonometric projection
- 🖼️ Manual image rendering using MiniLibX (a basic graphics library provided by 42)

## 🛠️ Technologies Used

- **C** (C99 standard)
- **MiniLibX** – a lightweight graphics library (X11-based)
- **Makefile** for compilation
- **Math.h** – used for trigonometric computations
- **42 Norminette** compliant code

## 🎮 Controls

| Key       | Action                |
|-----------|------------------------|
| W / S     | Move forward / back    |
| A / D     | Strafe left / right    |
| Left / Right Arrow | Rotate camera |

## 🗂️ Project Structure

Cube3D/
├── src/ # Core engine logic
│ ├── raycasting/ # Ray-wall intersection and projection
│ ├── render/ # Image drawing logic
│ ├── input/ # Key handling
│ ├── parser/ # Map file parsing and validation
│ └── main.c # Entry point
├── includes/ # Header files
├── maps/ # Example .cub map files
├── textures/ # Wall textures (XPM format)
├── Makefile
└── README.md


## 📦 Build Instructions

1. Clone the repo:
   ```bash
   git clone https://github.com/OkuM1/Cube3D
   cd Cube3D
    make
   ./cub3D maps/map1.cub

Example Map:
1111111111
1000000001
1011111101
1000000001
1111111111

What I Learned

    Manual implementation of a basic 3D engine using mathematics and geometry

    Understanding of raycasting, projection planes, and camera rotation

    Handling manual pixel manipulation with limited graphics APIs

    Dealing with parsing, memory leaks, and performance bottleneck
