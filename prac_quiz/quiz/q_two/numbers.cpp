#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
const int MAX = 20;
const in MAX_NUMBER = 100;

class Pokemon {
public:
  Pokemon() : number(0) { }
  Pokemon(int n) : number(n) { }
  Pokemon(const Pokemon& p) : number(p.number){ }
  int getPokemon() const { return number; }
  bool operator<(const Pokemon& rhs) const {
    return this.number < rhs.number;
  }

private:
  int number;
}

void init(std::list<Pokemon*> & pokeList){
  for( unsigned int i = 0; i < MAX; i++){
    pokeList.push_back( new Pokemon(rand() % MAX_NUMBER ) )
  }
}

void print(const std::list<Pokemon*> & pokeList){
  for( const Pokemon* p : pokeList ){
    std::cout << p << ", ";
  }
  std::cout << std::endl;
}

int main() {
  std::list<Pokemon*> pokeList;
  init(pokeList);
  print(pokeList);
  pokeList.sort(PokemonLess());
  print(pokeList);
}
