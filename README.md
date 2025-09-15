# Procedural Programming Final Project (a.y. 2021/2022)

This project is the final assignment for the **Procedural Programming with Laboratory** course.  
The base project was extended with several additional features and design choices:

- Added graphical elements (some of which change depending on the chosen class).  
- Introduced a maximum and minimum deck size constraint.  
- Implemented gameplay rules:
  - No attacks allowed during the first turn.  
  - No direct attacks permitted if the player has fewer creatures on the field than the opponent.  
- When the player has no cards in hand and chooses *Fight* or *Play Card*, the game now allows drawing a new card, which can then be placed and used to attack.  
- Added three dedicated functions to display the **title**, **story**, and **credits**.  
- Improved user interaction by adding several confirmation prompts (loops and variables) to validate player choices.  

---

## How to Run

The project consists of three source files:  
- `main.c`  
- `gamelib.c`  
- `gamelib.h`  

To compile and run the game, use a C compiler such as `gcc`. From the project directory:  

```bash
gcc main.c gamelib.c -o game
./game
```
