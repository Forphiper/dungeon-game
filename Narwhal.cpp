#include "Narwhal.h"

Narwhal::Narwhal()
{
    name = "Narnar";
    age = 13;
    tusksize= 1.7;
}

Narwhal::Narwhal(string name, int age, float tusksize)
{
    this->name = name;
    this->age = age;
    this->tusksize = tusksize;
}

Narwhal::~Narwhal()
{

}

void Narwhal::eat()
{
    cout << name << " eats some squid" << endl;
}

void Narwhal::makeSound()
{
    cout << name << " makes some narwhal sound" << endl;
}

void Narwhal::swim()
{
    cout << name << " swims to cold water" << endl;
}