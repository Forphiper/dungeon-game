#pragma once

#include <iostream>
#include <string>

using namespace std;

class Character
{
protected: // works the same as private, but children classes can access them
    // attributes
    int hp, hpMax, str, def, agi;
public:
    Character();
    ~Character();

    // behaviors/methods
    void setupStats(int _hp, int _str, int _def, int agi_);
    void displayStats();

    int getHP();
    int getHPMax();
    int getAGI();

    int getDamage();
    void takeDamage(int dmg);

    string getName();
};