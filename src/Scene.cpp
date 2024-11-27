#include "Scene.hpp"

Scene::Scene()
{
  this->name = "";
  this->musicPath = "";
}

Scene::Scene(std::string name, std::string musicPath, int numberOfFrames)
{
  this->name = name;
  this->musicPath = DEFAULT_MUSIC_PATH + musicPath;
  if (musicPath.length())
  {
    this->playMusic();
  }
  this->numberOfFrames = numberOfFrames;
}

void Scene::playMusic()
{
  if (this->music.openFromFile(this->musicPath))
  {
    this->music.setVolume(40);
    this->music.play();
  }
  else
  {
    std::cerr << "(Scene.cpp) Error while playing Music" << std::endl;
  }
}

void Scene::setMusicPath(std::string _musicPath)
{
  this->musicPath = DEFAULT_MUSIC_PATH + _musicPath;
}

void Scene::stopMusic()
{
  this->music.stop();
  while (this->music.getStatus() != sf::SoundSource::Stopped)
  {
    ; // Wait for music to stop
  }
}

void Scene::addText(std::string _string, int x, int y, int size, std::string fontPath = "assets/font/PressStart2P-Regular.ttf")
{
  sf::Text *text = new sf::Text();
  sf::Font *font = new sf::Font();
  if (font->loadFromFile(fontPath))
  {
    text->setFont(*font);
  }
  text->setString(_string);
  text->setCharacterSize(size);
  text->setFillColor(sf::Color::White);
  text->setOutlineColor(sf::Color::Black);
  text->setOutlineThickness(2);
  text->setPosition(x, y);

  this->sceneTexts.push_back(text);
}

void Scene::addTextCenter(sf::RenderWindow *window, std::string _string, int size, int r = 0, int g = 0, int b = 0, std::string fontPath = "assets/font/PressStart2P-Regular.ttf")
{
  sf::Text *text = new sf::Text();
  sf::Font *font = new sf::Font();
  if (font->loadFromFile(fontPath))
  {
    text->setFont(*font);
  }
  else
  {
    std::cerr << "Font at " << fontPath << " could not be loaded" << std::endl;
  }
  text->setString(_string);
  text->setCharacterSize(size);
  text->setFillColor(sf::Color(r, g, b));
  text->setOutlineColor(sf::Color::Black);
  text->setOutlineThickness(1);
  text->setPosition(window->getSize().x / 2 - text->getGlobalBounds().width / 2, window->getSize().y / 2 - text->getGlobalBounds().height / 2);

  this->sceneTexts.push_back(text);
}

void Scene::addTextCenterWithY(sf::RenderWindow *window, std::string _string, int size, int y, int r = 0, int g = 0, int b = 0, std::string fontPath = "assets/font/PressStart2P-Regular.ttf")
{
  sf::Text *text = new sf::Text();
  sf::Font *font = new sf::Font();
  if (font->loadFromFile(fontPath))
  {
    text->setFont(*font);
  }
  else
  {
    std::cerr << "Font at " << fontPath << " could not be loaded" << std::endl;
  }
  text->setString(_string);
  text->setCharacterSize(size);
  text->setFillColor(sf::Color(r, g, b));
  text->setOutlineColor(sf::Color::Black);
  text->setOutlineThickness(1);
  text->setPosition(window->getSize().x / 2 - text->getGlobalBounds().width / 2, y);

  this->sceneTexts.push_back(text);
}

void Scene::changeOpacityText(int position, int opacity)
{
  sf::Text *text = this->getTextAt(position);
  sf::Color color = text->getFillColor();
  if (color.a > opacity)
  {
    color.a -= 1;
  }
  else if (color.a < opacity)
  {
    color.a += 1;
  }
  text->setFillColor(color);
  this->sceneTexts.at(position) = text;
}

void Scene::loadFromFile(std::string path, sf::RenderWindow *window)
{
  std::string name;
  sf::Color color;
  std::vector<sf::Text *> texts;
  std::vector<sf::RectangleShape *> rectangles;
  std::string musicPath;

  try
  {
    YAML::Node object = YAML::LoadFile(DEFAULT_SCENE_PATH + path);
    musicPath = object["Music"].as<std::string>();
    this->setMusicPath(musicPath);

    if (object["Background"].IsSequence() && object["Background"].size() == 3)
    {
      std::vector<int> colorMap = object["Background"].as<std::vector<int>>();
      bgColor = sf::Color(colorMap.at(0), colorMap.at(1), colorMap.at(2));
    }

    name = object["Name"].as<std::string>();
    this->setName(name);

    for (int8_t i = 0; i < object["Texts"].size(); i++)
    {
      if (object["Texts"][i]["Centered"].IsDefined() && object["Texts"][i]["Centered"].as<bool>())
      {
        std::string text = object["Texts"][i]["Text"].as<std::string>();
        int size = object["Texts"][i]["Size"].as<int>();
        int r = object["Texts"][i]["Red"].as<int>();
        int g = object["Texts"][i]["Green"].as<int>();
        int b = object["Texts"][i]["Blue"].as<int>();
        if (!object["Texts"][i]["YCoords"].IsDefined())
        {
          this->addTextCenter(window, text, size, r, g, b);
        }
        else
        {
          int y = object["Texts"][i]["YCoords"].as<int>();
          this->addTextCenterWithY(window, text, size, y, r, g, b);
        }
      }
      else
      {
        std::string text = object["Texts"][i]["Text"].as<std::string>();
        int size = object["Texts"][i]["Size"].as<int>();
        int r = object["Texts"][i]["Red"].as<int>();
        int g = object["Texts"][i]["Green"].as<int>();
        int b = object["Texts"][i]["Blue"].as<int>();
        int x = object["Texts"][i]["XCoords"].as<int>();
        int y = object["Texts"][i]["YCoords"].as<int>();
        this->addText(text, x, y, size);
      }
    }

    if(object["nextSceneFile"].IsDefined())
    {
      this->nextScene = object["nextSceneFile"].as<std::string>();
    }
  }
  catch (YAML::BadFile e)
  {
    std::cerr << "Error while loading Scene: " << e.msg << std::endl;
    std::cerr << e.what() << std::endl;
    return;
  }
  catch (YAML::Exception e)
  {
    std::cerr << "Error: " << e.msg << std::endl;
    std::cerr << e.what() << std::endl;
  }
}