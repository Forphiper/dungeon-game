#pragma once
#include "Animal.h"

class Narwhal : public Animal
{
public:
    float tusksize;
    Narwhal();
    Narwhal(string name, int age, float tusksize);
    ~Narwhal();

    void eat();
    void makeSound();
    void swim();

};