# cub3D
A raycasting engine inspired by Wolfenstein 3D
42 School Project | C Programming & Graphics Implementation

Gameplay Preview
![Screenshot from 2025-04-21 12-48-20](https://github.com/user-attachments/assets/eb4113a8-0564-4d4d-8a85-81520d8c4d37)


# 📖 Overview
A minimalist 3D game engine using raycasting technology to project a first-person perspective of a dynamically generated maze. Built from scratch in C using the MLX42 graphics library, this project demonstrates core principles of computer graphics and low-level system programming. 

# 🎮 Features
Custom map system with .cub file parsing:

Wall textures (png files)

flashlight if both the ceiling and floor are black (F to toggle on and off);

Floor/ceiling colors (RGB values)

Player spawn position/direction (N, E, S, W)

# Raycasting engine:

DDA (Digital Differential Analysis) algorithm for efficient wall detection

Dynamic wall height calculation based on player distance

# Interactive controls:

WASD movement

R to reload gun.

Mouse/arrow key camera rotation

F to toggle flashlight on and off (only works if the value of the floor and ceiling are 0)

SPACE BAR to open and close doors (need to be close and looking at the door)

LEFT_SHIFT to sprint

ESC to exit

# Advanced graphics:

Gun animation system (idle/walk/reload/fire states)

Sprite sheet sequencing

Texture mapping

Minimap overlay

Door interaction system

# 🛠️ Installation

clone repo

cd cub3d
make bonus

# 🕹️ Usage

./cub3d_bonus maps/jerda.cub

# 🗺️ MAP:

The SO NO WE EA image paths are used as the texture for the wall facing the specified direction ( south north west east)
F is the rgb color for the floor
C is the rgb color for the ceiling

1 is a wall 0 is a walkable space

D is a closed door

N S E W is the poisition of the player and the direction he is facing (north south east west)

spaces can be added to the map to create complex shapes


This is an example of a valid map:

```
SO textures/jerda1.png
NO textures/jerda1.png
WE textures/jerda1.png
EA textures/jerda1.png

F 0,0,0
C 0,0,0

11111111111111111111
10000010000000000001
10111101111111111011
10100000000000001001
10101111111111101011
10101000000000101001
1D101011111110101111
10101010000010100001
10101010111110111101
10101010100010000101
10101010101111111101
10101010100000000001
10101011111111111111
101010000D0000000001
1D101111111011111101
1N000000001000000001
11111111101011111111
10000000000000000001
10111111111111111011
10000000000000000001
11111111111111111111
```
