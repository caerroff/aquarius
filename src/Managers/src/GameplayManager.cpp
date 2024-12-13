#include "../include/GameplayManager.hpp"

void GameplayManager::setModeGameplay(sf::RenderWindow *window)
{
  this->window = window;
  keyState.fill(true);
  this->fpsCounter->setPosition(1210, 30);
  sf::Font *font = new sf::Font();
  font->loadFromFile("assets/font/PressStart2P-Regular.ttf");
  this->fpsCounter->setCharacterSize(30);
  this->fpsCounter->setFillColor(sf::Color(255, 255, 255));
  this->fpsCounter->setOutlineColor(sf::Color(0, 0, 0));
  this->fpsCounter->setOutlineThickness(2);
  this->fpsCounter->setFont(*font);
  this->currentMode = GAMEPLAY_CODE;
  this->window->setKeyRepeatEnabled(true);
}

void GameplayManager::stopModeGameplay()
{
  this->currentMode = OFF_CODE;
}

int GameplayManager::getCurrentMode()
{
  return this->currentMode;
}

int GameplayManager::getTileAt(sf::Vector2f position)
{
  std::cout << "Position x: " << position.x << std::endl;
  std::cout << "Position y: " << position.y << std::endl;
  return 0;
}

void GameplayManager::update(sf::RenderWindow *window)
{
  sf::Event e;
  check_camera();
  while (window->pollEvent(e))
  {
    if (e.type == sf::Event::Closed)
    {
      window->close();
      return;
    }
    if (e.type == sf::Event::KeyPressed)
    {
      switch (e.key.code)
      {
      case sf::Keyboard::Equal:
        map->getView()->zoom(0.9);
        break;
      case sf::Keyboard::Dash:
        map->getView()->zoom(1.1);
        break;
      default:
        break;
      }
#ifdef DEBUG
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && !this->keyState[e.key.code] && this->nextMapPath.length() > 0)
      {
        this->switchNextMap();
        std::cout << "(DEBUG) Next Map" << std::endl;
        this->keyState[e.key.code] = true;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2) && !this->keyState[e.key.code])
      {
        std::cout << "(DEBUG) Reload current map " << this->currentMapPath << std::endl;
        this->nextMapPath = this->currentMapPath;
        this->switchNextMap();
        this->keyState[e.key.code] = true;
      }
#endif
    }
    if (e.type == sf::Event::KeyReleased)
    {
      this->keyState[e.key.code] = false;
    }
  }

  window->clear(map->getClearColor());
  map->update(window);
  window->setView(window->getDefaultView());
#ifdef DEBUG
  sf::Time elapsedTime = chrono.getElapsedTime();

  float fps = std::round(1.f / elapsedTime.asSeconds());
  std::string fpsString = std::to_string(fps);
  fpsCounter->setString(fpsString.substr(0, 2));
  window->draw(*fpsCounter);
  chrono.restart();
#endif
}

void GameplayManager::check_camera()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    map->setViewVelocity(sf::Vector2f(map->getViewVelocity().x, -20 * 0.001f * window->getView().getSize().y));
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    map->setViewVelocity(sf::Vector2f((20 * 0.001f * window->getView().getSize().x), map->getViewVelocity().y));
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    map->setViewVelocity(sf::Vector2f((-20 * 0.001f * window->getView().getSize().x), map->getViewVelocity().y));
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    map->setViewVelocity(sf::Vector2f(map->getViewVelocity().x, 20 * 0.001f * window->getView().getSize().y));
  }
}

void GameplayManager::addCharacter()
{
  this->map->addCharacter(new Character());
}

void GameplayManager::addTile(Tile *tile)
{
  ;
}

void GameplayManager::removeCharacterAt(int position)
{
  this->map->removeCharacterAt(position);
}

void GameplayManager::setMusicPath(const char *_musicPath)
{
  std::string path = std::string(DEFAULT_MUSIC_PATH) + std::string(_musicPath);
  this->musicPath = (char *)calloc(path.length(), sizeof(char));
  for (int i = 0; i < path.length(); i++)
  {
    this->musicPath[i] = path[i];
  }
}

void GameplayManager::playMusic()
{
  this->music.setLoop(1);
  if (this->music.openFromFile(this->musicPath))
  {
    this->music.setVolume(40);
    this->music.play();
  }
}

void GameplayManager::stopMusic()
{
  this->music.stop();
  while (this->music.getStatus() != sf::SoundSource::Stopped)
  {
    ; // Wait for music to stop
  }
}

void GameplayManager::characterTextBox(int characterIndex, char *text)
{
  sf::Texture *faceSprite = this->map->getCharacterAt(characterIndex)->getFaceSprite();
  sf::RectangleShape *textBox = new sf::RectangleShape(sf::Vector2f(TEXTBOX_WIDTH, TEXTBOX_HEIGHT));
  textBox->setPosition(TEXTBOX_X, TEXTBOX_Y);
  textBox->setFillColor(sf::Color::Black);
  textBox->setOutlineColor(sf::Color::White);
  textBox->setOutlineThickness(5);
  sf::Text *textObj = new sf::Text();
  sf::Font *font = new sf::Font();
  font->loadFromFile(DEFAULT_FONT_PATH);
  textObj->setFont(*font);
  textObj->setString(text);
  textObj->setCharacterSize(24);
}

int GameplayManager::switchNextMap()
{
  this->currentMapPath = this->nextMapPath;
  this->nextMapPath = "";
  this->loadMap(currentMapPath, this->window);
  return 0;
}

void GameplayManager::loadMap(std::string _filePath, sf::RenderWindow *window)
{
  this->currentMapPath = _filePath;
  std::future<Map*> futureMap = std::async(&loadMapFromFile, DEFAULT_MAP_PATH + _filePath, window);  
  sf::Text text;
  sf::Font font;
  font.loadFromFile(DEFAULT_FONT_PATH);
  text.setFont(font);
  text.setFillColor(sf::Color::White);
  text.setCharacterSize(20);
  text.setPosition(sf::Vector2f(100, 100));
  text.setString("Loading");
  // while(! futureMap._Is_ready())
  while(futureMap.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready)
  {
    window->clear(sf::Color(25, 5, 0));
    window->draw(text);
    text.setString(text.getString() + ".");
    window->display();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
  }
  this->map = futureMap.get();
}