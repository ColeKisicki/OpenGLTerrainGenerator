# OpenGL Terrain Generator

This procedural terrain generator uses the marching cubes algorithm and random noise to create a 3d model of terrain.

## Table of Contents

- [OpenGL Terrain Generator](#opengl-terrain-generator)
  - [Table of Contents](#table-of-contents)
  - [Project Description](#project-description)
  - [Features](#features)
  - [Naviagation](#naviagation)

## Project Description

The Procedural Terrain Generator leverages the power of the marching cubes algorithm and random noise to dynamically generate detailed 3D terrain models. This project is aimed at creating realistic and visually appealing terrains.

## Features

- Marching Cubes Algorithm: The heart of this terrain generator is the marching cubes algorithm, a powerful technique for creating complex 3D surfaces based on volumetric data. It enables the creation of smooth and detailed terrains using correct normals for each vertex generated. The vertices are also shared between the triangles to optimize performance and to help maintain consistant normals on each face.

- Random Noise Generation: The generator utilizes random noise functions to add organic and natural variations to the terrain. By adjusting parameters like frequency and amplitude, users can control the level of detail and randomness in the generated terrain.

- Customizable Parameters: Users have the flexibility to adjust various parameters, such as terrain size, isolevel (threshold), and noise settings. This customization allows for the creation of terrains that suit specific project requirements.

- Color Mapping: To enhance the realism of the generated terrains, a color mapping feature has been implemented. This feature assigns different colors to different parts of the terrain based on elevation, steepness, or other criteria, giving the terrain a more lifelike appearance.

- Terrain Exploration: Users can navigate and explore the generated terrains in real-time, providing an interactive experience for evaluating and using the terrain models.


## Naviagation

The naviagation is similar to a first person shooter. The camera can be moved forward/left/backward/right using 'wasd' and the camera can be rotated using the mouse.
