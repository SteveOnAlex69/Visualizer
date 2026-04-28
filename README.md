# Data Structure and Algorithm Visualizer

- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [Technical Requirements](#technical-requirements)
- [Installation & Build Guide](#installation--build-guide)
- [Demo](#demo)
- [License](#license)

## Project Overview

This is a standalone, interactive C++ application designed to visualize core Data Structures and Algorithms. The motivation behind this project was to bridge the gap between reading static textbook code and actually understanding how pointers, memory, and balancing mechanics change in real-time. 

Instead of writing a monolithic script where the math and graphics are tangled together, this visualizer runs on a strictly **decoupled state-machine architecture**. The core C++ logic structures (like the AVL tree and Dijkstra's flood-fill) operate entirely in a vacuum. A middleman controller takes snapshots of the data and passes them to the SFML rendering engine. This prevents spaghetti code and guarantees that the visual animations never interfere with the actual computer science math.

Hopefully you have an enjoyable time playing around with this program, and hopefully it should be intuitive enough to use without friction :P

**Implemented Structures:**
1. Singly Linked List
2. Hash Table (Chaining)
3. AVL Tree
4. Trie (String-based)
5. Kruskal's Algorithm (Minimum Spanning Tree)
6. Dijkstra's Algorithm (Shortest Path)

## Key Features
* **Step-by-Step Playback:** Navigate forward, backward, or skip to the end of any algorithm, fully synchronized with an on-screen pseudocode highlighter.
* **Native OS File Loading:** Integrated `portable-file-dialogs.h` allows you to open native Windows file explorers to load external `.txt` datasets easily.
* **Dynamic Camera Control:** Infinitely pan across the canvas using mouse-drag vectors to view massive graphs that expand beyond the screen bounds.
* **Custom UI Engine:** The interface is built from a bespoke `.des` deserializer, avoiding hardcoded UI coordinates and allowing for deep nesting of interactive buttons and text boxes.
* **Mathematical Easing:** Node animations utilize sigmoid functions to accelerate and decelerate naturally, rather than moving at a rigid, linear speed.
* **Interactive Environments:** Features multiple themes, including a parallax 3D starfield and a cursor-reactive particle grid.

## Technical Requirements
* **Platform:** Windows 11 (64-bit)
* **Programming Language:** C++17 standard
* **Build System:** CMake Version 3.22+
* **Graphics Library:** SFML 3.0.2 *(Note: Required binaries are bundled locally in the repo, so you do not need a system-wide installation)*
* **IDE:** Visual Studio 2022 (Community Edition is fine)

## Installation & Build Guide

The build process is fully automated via CMake. It is configured to automatically link the local SFML libraries and transfer the required `.dll` files into your output folder.

1. Download [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) and ensure the **"Desktop development with C++"** workload is installed.
2. Clone this repository or download and extract the ZIP file.
3. Open Visual Studio 2022 and select **"Open a local folder"**. Choose the root folder of this project.
4. Wait a few seconds for the background CMake cache generation to complete (the Output console will state *"CMake generation finished"*).
5. On the top toolbar, change the build configuration dropdown from "x64-Debug" to **"x64-Release"**. *(Warning: Debug mode lacks compiler optimizations and will severely drop the animation framerate).*
6. Next to the green Play button, ensure `DataVisualizer.exe` is selected as the Startup Item.
7. Click **Build** (or press `Ctrl+Shift+B`).
8. Once compiled, navigate to the newly generated `build/` folder in your File Explorer and run `DataVisualizer.exe`. 

## Demo
Youtube Video Link: 


## License
This is an open educational tool. Feel free to use, study, and build upon the code. See the `LICENSE` file for the full legal text.