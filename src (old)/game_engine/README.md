**DISCLAIMER: I DO NOT KNOW WHAT I AM DOING**

Architecture:

Game and game engine, both in C++
As both are in C++, game and game engine implementations can be equally efficient
Thus the game engine should provide as much freedom as possible for the game, only implementing some of the basic stuff (rendering, etc.) and providing common helper definitions (blocks, entities, etc.)

Server that runs game logic, client that runs graphics and UI
Locally bound together (client should be given references to server data)
Otherwise have a network module