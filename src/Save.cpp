#include "Save.hpp"

Save *createSaveFile()
{
    Save *save = (Save *)malloc(sizeof(Save));
    save->time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    save->name = (char *)malloc(sizeof(char) * 20);
    save->name = "";
    save->player = (Player *)malloc(sizeof(Player));
    return save;
}

void saveGame(Save *save)
{
    // create a file name save.sav
    std::ofstream saveFile("save.sav", std::ofstream::out | std::ofstream::trunc);
    // write the save file in hexadecimal
    saveFile << std::hex << save->time << std::endl;
    saveFile << save->name << std::endl;

    saveFile.close();
}