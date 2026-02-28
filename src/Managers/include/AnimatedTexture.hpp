#ifndef ANIMATED_TEXTURE
#define ANIMATED_TEXTURE
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#include <cstdint>
struct AnimatedTexture {
    uint8_t lenTextures;
    uint8_t textureIndex;
    uint16_t intervalMs = 100;
    sf::Texture *textures[10];
};

#endif
