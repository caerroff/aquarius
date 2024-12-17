### Master branch status
[![CI](https://github.com/caerroff/aquarius/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/caerroff/aquarius/actions/workflows/ci.yml)
### Develop branch status
[![CI](https://github.com/caerroff/aquarius/actions/workflows/ci.yml/badge.svg?branch=develop)](https://github.com/caerroff/aquarius/actions/workflows/ci.yml)

# Aquarius-game
 A game about the Aquarius album from Haken.

# Installing

The game has a few dependencies:
- CMake
- a C++ compiler for CMake (tested with g++, clang and the Visual Studio 2022 C++ compiler)

And some dependencies are installed when building the project with CMake (sfml and yaml-cpp for now), thus having an internet when building the project is required.

To build an executable from source on your machine, a Makefile has been created to store the useful commands:
- To create a `Release` version of the game, you can simply run the following command at the root of the project
```
make
```

- To create a `Debug` version of the game, you can use
```
make debug
```

In both cases, the executable will be created in the following directory:
`/build/bin/aquarius`
*OR* on Windows
`/build/bin/Release/aquarius.exe`

## C++ Standards
The game uses cxx_std_17 standards

## Platforms
The game is tested on the latest MacOS versions (arm64 Mx Apple processors), Linux (Arch and Ubuntu, latest versions) and Windows 11 (Visual Studio 2022 compiler).

## Contribution
Any contribution is always welcome and will be reviewed in the shortest delays. You can check what issues are currently open in the Issues section, or create your own issue to address a bug or feature request you have.

# Game

## Gameplay
The gameplay will be pretty basic. We follow the story of the girl blessed by the curse. The game follows the album's story (as much as possible) and tries to tell the story in a different media, while still keeping the essential in.
- Scenes (kinda like cinematics but in a 2D game)
- Exploration gameplay 
- Dialogues
- Choices

## Music
I will try my best to make as many songs from the original album in an 16-bit ish version. It may not be perfect, and I will certainely need some other songs (ambient songs, title screen etc..)

## Sprites / Graphics
They will be hand-drawn and try to give the same vibes as the ones **I** had while first listening to this album. The interpretation will of course be very subjective.

## Code and licensing
The code should end up being open source, either the whole game or just the engine.

# About how it works
### The Managers
Managers are glorified singletons. They can only be instantiated once, and will manage everything about a Scene or a Gamescene, from player, to maps, to actions, to what the next scene or map should be.

### The global assets (Maps, Characters etc...)
They are stored in yaml files.
I use the library [YAML-cpp](https://github.com/jbeder/yaml-cpp).
The parser allows me to read the objects and render the appropriate assets in the game.
