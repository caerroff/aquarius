#include "../include/GameplayManager.hpp"

void GameplayManager::setModeGameplay()
{
    this->currentMode = GAMEPLAY_CODE;
}

void GameplayManager::stopModeGameplay()
{
    this->currentMode = OFF_CODE;
}

int GameplayManager::getCurrentMode()
{
    return this->currentMode;
}

void GameplayManager::update(sf::RenderWindow* window)
{
    window->clear(*map->getClearColor());
    for (int i = 0; i < this->map->getCharacterCount(); i++)
    {
        this->map->getCharacterAt(i)->update(window);
    }
    for(int i = 0; i < this->map->getActionCount(); i++)
    {
        this->map->getActionAt(i)->update(window, 0);
    }
}

void GameplayManager::addCharacter()
{
    this->map->addCharacter(new Character());
}

void GameplayManager::addTile(Tile* tile)
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
    this->musicPath = (char*)calloc(path.length(), sizeof(char));
    for(int i = 0; i < path.length(); i++)
    {
        this->musicPath[i] = path[i];
    }

}

void GameplayManager::playMusic()
{
    this->music.setLoop(1);
    if(this->music.openFromFile(this->musicPath))
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

void GameplayManager::characterTextBox(int characterIndex, char* text)
{
    sf::Texture* faceSprite = this->map->getCharacterAt(characterIndex)->getFaceSprite();
    sf::RectangleShape* textBox = new sf::RectangleShape(sf::Vector2f(TEXTBOX_WIDTH, TEXTBOX_HEIGHT));
    textBox->setPosition(TEXTBOX_X, TEXTBOX_Y);
    textBox->setFillColor(sf::Color::Black);
    textBox->setOutlineColor(sf::Color::White);
    textBox->setOutlineThickness(5);
    sf::Text* textObj = new sf::Text();
    sf::Font* font = new sf::Font();
    font->loadFromFile(DEFAULT_FONT_PATH);
    textObj->setFont(*font);
    textObj->setString(text);
    textObj->setCharacterSize(24);

}

int GameplayManager::switchNextMap()
{
    return 1;
}

void GameplayManager::loadMap(char* _filePath)
{
    if(this->map != NULL)
    {
        delete this->map;
    }
    this->map = Map::loadFromFile(_filePath);
}

void GameplayManager::loadDefaultMap()
{
    if(this->map != NULL)
    {
        delete this->map;
    }
    this->map = new Map();
    this->map->setClearColor(new sf::Color(100,100,100));
    Player* player = new Player("Girl", 1);
    player->setBody(new sf::RectangleShape(sf::Vector2f(32,32)));
    player->getBody()->setPosition(sf::Vector2f(0,0));
    player->setSprites("Characters/Father/sprites.png");
    map->addCharacter(player);

}