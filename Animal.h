#pragma once
#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
    string name;
    int age;

    Animal();
    Animal(string name, int age);
    ~Animal();

    virtual void eat();
    virtual void makeSound();
    void display();
};