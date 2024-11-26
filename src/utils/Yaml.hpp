#ifndef YAML_PARSER
#define YAML_PARSER
#include "../Scene.hpp"
#include "../Collidables/Player.hpp"

class Yaml
{
public:
    /**
     *Reads a scene and returns a pointer to the created object
     *@param path The path to the file containing the scene
     *@return a pointer to the Scene object
     */
    Scene *readScene(const char *path);
};

#endif