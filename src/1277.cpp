#include <iostream>
#include "1277.hpp"

int main() {
    Pokedex pokedex("pokedex");
    pokedex.pokeAdd("Pikachu", 25, "electric");
    pokedex.pokeAdd("Bulbasaur", 1, "grass");
    pokedex.pokeAdd("Squirtle", 7, "water");
    std::cout << pokedex.pokeAdd("Squirtle", 7, "water") << '\n';
    pokedex.pokeAdd("Charizard", 6, "fire#flying");
    pokedex.pokeAdd("Gyarados", 130, "water#flying");
    pokedex.pokeAdd("Palkia", 484, "water#dragon");
    pokedex.pokeAdd("Garchomp", 445, "ground#dragon");
    pokedex.pokeAdd("TestPM", 66666666, "fire#water#flying#ground#dragon");

    std::cout << pokedex.pokeFind(445) << '\n';
    std::cout << pokedex.typeFind("dragon") << '\n';

    pokedex.pokeDel(66666666);

    std::cout << pokedex.typeFind("water#dragon") << '\n';
    std::cout << pokedex.attack("electric", 130) << '\n';
    std::cout << pokedex.catchTry() << '\n';

    return 0;
}
