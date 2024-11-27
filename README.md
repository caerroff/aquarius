[![CI](https://github.com/caerroff/aquarius/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/caerroff/aquarius/actions/workflows/ci.yml)

# Aquarius-game
 A game about the Aquarius album from Haken.

## Gameplay
The gameplay will be pretty basic. We follow the story of the girl blessed by the curse. The game follows the album's story (as musch as possible) and tries to tell the story in a different media, while still keeping the essential in.
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

## About how it works
### The Managers
Managers are glorified singletons. They can only be instantiated once, and will manage everything about a Scene or a Gamescene, from player, to maps, to actions, to what the next scene or map should be.

### The global assets (Maps, Characters etc...)
They are just yaml files.
I use the library [!YAML-cpp(https://github.com/jbeder/yaml-cpp)]
