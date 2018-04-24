#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
const int MAX = 20;
const int MAX_NUMBER = 100;

class Pokemon {
public:
  Pokemon() : number(0) { }
  Pokemon(int n) : number(n) { }
  Pokemon(const Pokemon& p) : number(p.number){ }
  int getPokemon() const { return number; }
  bool operator<(const Pokemon& rhs) const {
    return number < rhs.number;
  }

private:
  int number;
};

class PokemonLess {
public:
  bool operator()(const Pokemon* lhs, const Pokemon* rhs) const {
    return lhs->getPokemon() < rhs->getPokemon();
  }
};

std::ostream& operator<<(std::ostream& cout, const Pokemon* pokeList){
  return cout << pokeList->getPokemon();
}

void init(std::list<Pokemon*> & pokeList){
  for( unsigned int i = 0; i < MAX; i++){
    pokeList.push_back( new Pokemon(rand() % MAX_NUMBER ) );
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
  pokeList.sort(
    [](const Pokemon* lhs, const Pokemon* rhs){ return lhs->getPokemon() > rhs->getPokemon(); }
  );
  print(pokeList);
}
