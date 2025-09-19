# Pong Game (C++ & SFML)

A simple **Pong game** built using C++ and SFML. This project demonstrates collision detection, paddle movement, scoring, and a Game Over screen with final scores.

---

## Features

- **Two-player mode**
  - Player 1: Controlled with **mouse** (or keyboard optionally)  
  - Player 2: Controlled with **W/S keys** (or arrow keys for testing)
- **Ball physics**
  - Bounces off top and bottom edges
  - Inverts direction when hitting paddles
  - Speed gradually increases on paddle hits
- **Scoring system**
  - Score increments when the ball passes a paddle
  - Game ends when a player reaches 5 points
- **Game Over screen**
  - Displays final scores and the winner
  - Winner’s score highlighted for clarity
- Smooth **frame-independent movement** using `deltaTime`

---

## Installation

1. **Install SFML**  
   Follow the official guide: [SFML Setup](https://www.sfml-dev.org/tutorials/2.5/)

2. **Clone, Compile, and Run**
```bash
git clone https://github.com/Hemeshwer0001/Pong.git
cd Pong
g++ Pong.cpp -o Pong -lsfml-graphics -lsfml-window -lsfml-system
./Pong
