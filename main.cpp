#include <iostream>
#include <string>
#include "Animal.h"
#include "Narwhal.h"
#include "SDL.h"

using namespace std;

int main() {
    cout << "Hello World" << endl;

    Animal a1("jeff", 48);
    a1.eat();
    a1.makeSound();
    a1.display();

    Narwhal n1("unicorn", 22, 2.1);
    n1.eat();
    n1.makeSound();
    n1.swim();

    Animal *aPtr = new Narwhal("kelp", 3, 0.5);
    aPtr->eat();
    aPtr->makeSound();
    aPtr->display();

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    std::cout << "Hello SDL2 with C++" <<std::endl;

    SDL_Quit();

    return 0; 
}