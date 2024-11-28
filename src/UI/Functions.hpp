#ifndef FUNCTIONS_UI
#define FUNCTIONS_UI
#include "Dialogue.hpp"
#include <iostream>

/**
 * Loads a dialogue from a YAML Node
 * @param node the node containing the dialogue
 * @return a pointer to the created dialogue
 */
Dialogue *loadDialogueFromNode(YAML::Node node)
{
  std::string content = node["content"].as<std::string>();
  Dialogue *dialogue = (Dialogue *)malloc(sizeof(Dialogue));
  if (node["author"].IsDefined() && !node["author"].IsNull())
  {
    std::string author = node["author"].as<std::string>();
    dialogue = new Dialogue(content, author);
  }
  else
  {
    dialogue = new Dialogue(content);
  }
  return dialogue;
}

#endif