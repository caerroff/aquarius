#include "Scene.hpp"

Scene::Scene()
{
    this->name = "";
    this->musicPath = "";
}

Scene::Scene(char *name, char *musicPath, int numberOfFrames)
{
    this->name = name;
    this->musicPath = musicPath;
    this->playMusic();
    this->numberOfFrames = numberOfFrames;
}

void Scene::playMusic()
{
    this->music.openFromFile(this->musicPath);
    this->music.setVolume(40);
    this->music.play();
}

void Scene::setMusicPath(char *_musicPath)
{
    this->musicPath = _musicPath;
}

void Scene::stopMusic()
{
    this->music.stop();
    while (this->music.getStatus() != sf::SoundSource::Stopped)
    {
        ; // Wait for music to stop
    }
}

void Scene::addText(char *_string, int x, int y, int size, char *fontPath = "assets/font/PressStart2P-Regular.ttf")
{
    sf::Text *text = new sf::Text();
    sf::Font font;
    font.loadFromFile(fontPath);
    text->setFont(font);
    text->setString(_string);
    text->setCharacterSize(size);
    text->setFillColor(sf::Color::White);
    text->setOutlineColor(sf::Color::Black);
    text->setOutlineThickness(2);
    text->setStyle(sf::Text::Bold);
    text->setPosition(x, y);
    sceneTexts.push_back(text);
}

void Scene::addTextCenter(sf::RenderWindow *window, char *_string, int size, char *fontPath = "assets/font/PressStart2P-Regular.ttf")
{
    sf::Text *text = new sf::Text();
    sf::Font *font = new sf::Font();
    if (font->loadFromFile(fontPath))
    {
        text->setFont(*font);
    }
    else
    {
        printf("Font couldn't be loaded\n");
    }
    text->setString(_string);
    text->setCharacterSize(size);
    text->setFillColor(sf::Color::White);
    text->setOutlineColor(sf::Color::Black);
    text->setOutlineThickness(1);
    text->setPosition(window->getSize().x / 2 - text->getGlobalBounds().width / 2, window->getSize().y / 2 - text->getGlobalBounds().height / 2);

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

void Scene::loadFromFile(char *path, sf::RenderWindow *window)
{
    char *name;
    std::vector<sf::Text *> texts;
    std::vector<sf::RectangleShape *> rectangles;
    char *musicPath;
    int numberOfFrames;

    Scene* scene = new Scene();
    std::ifstream file;
    file.open(DEFAULT_SCENE_PATH + std::string(path));
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::string delimiter = "|";
            std::string token = line.substr(0, line.find(delimiter));
            if (token == "Scene")
            {
                name = (char *)line.substr(line.find(delimiter) + 1, line.length()).c_str();
            }

            if (token == "Action")
            {
                ;
            }

            if (token == "Music")
            {
                std::string musicPath = DEFAULT_MUSIC_PATH + line.substr(line.find(delimiter) + 1, line.length());
                char * path = (char*)calloc(musicPath.length(), sizeof(char));
                for(int i = 0; i < musicPath.length(); i++)
                {
                    path[i] = musicPath[i];
                }
                this->setMusicPath(path);
            }

            if (token == "Text")
            {
                //What's to retrieve in order:
                // - Text
                // - R
                // - G
                // - B
                // - Is it centered
                // - Position X
                // - Position Y
                // They are all separated by a | character
                std::string text = line.substr(line.find(delimiter) + 1, line.length());
                std::string textString = text.substr(0, text.find(delimiter));

                text = text.substr(text.find(delimiter) + 1, text.length());
                std::string r = text.substr(0, text.find(delimiter));
                text = text.substr(text.find(delimiter) + 1, text.length());
                std::string g = text.substr(0, text.find(delimiter));
                text = text.substr(text.find(delimiter) + 1, text.length());
                std::string b = text.substr(0, text.find(delimiter));
                text = text.substr(text.find(delimiter) + 1, text.length());
                std::string size = text.substr(0, text.find(delimiter));
                text = text.substr(text.find(delimiter) + 1, text.length());
                std::string isCentered = text.substr(0, text.find(delimiter));
                text = text.substr(text.find(delimiter) + 1, text.length());
                if (isCentered != "1")
                {
                    sf::Vector2f position = sf::Vector2f(std::stoi(text.substr(0, text.find(delimiter))), std::stoi(text.substr(text.find(delimiter) + 1, text.length())));
                }
                this->addTextCenter(window, (char*)textString.c_str(), std::stoi(size));
            }
        }
    }
    else
    {
        fprintf(stderr, "Couldn't open file\n");
    }
}