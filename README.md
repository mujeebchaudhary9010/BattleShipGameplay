# BattleShipGameplay
A 2D Battleship game built with C++. It features a tactical AI for both ship placement and attacking, along with a custom drag-and-drop system for the player.

# Key Logic & Gameplay
Menu Flow: The game starts with a main menu (Start, Leaderboard, Exit). After entering a player name, it moves to the placement screen.

1) Ship Placement: You can drag and drop ships onto the grid. While dragging, pressing R rotates the ship.

2) Locking In: Once the 'Start' button is clicked, ship positions are locked. You can't move them anymore, and the battle phase begins.

3)Combat & AI: * The computer AI places its ships randomly on a hidden grid.

.The AI uses a missile attack logic to find and sink your ships.

.You have 45 missiles total to win the game.

4) Visuals & Sound: Tiles change color based on hits and misses. I've integrated sound effects for firing and impacts.

5) Scoring: Points are awarded based on hits, and the game ends with a Win/Loss window depending on your performance.

# Built With
C++

SFML (Graphics, Audio, Events)
