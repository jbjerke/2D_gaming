#include<iostream>
#include<cstring>

class Pokemon{
public:
  Pokemon() : name(new char[1]),
    index(0),
    ad(0),
    defense(1/2*ad),
    hp(30){
      name[0] = '\0';
      std::cout<< "default" << std::endl;
    }

  Pokemon(const char* n, int i, int a, int d, int h) :
    name(new char[strlen(n) + 1]),
    index(i),
    ad(a),
    defense(d),
    hp(h) {
      strcpy(name, n);
      std::cout<< "convert" << std::endl;
    }

    // copy constructor
    Pokemon(const Pokemon& p) :
      name(new char[strlen(p.name) + 1]),
      index(p.index),
      ad(p.ad),
      defense(p.defense),
      hp(p.hp) {
        std::cout << "copy" << std::endl;
        strcpy(name, p.name);
      }

    // deconstructor
    ~Pokemon(){
      delete [] name;
    }

    // assignment operator
    Pokemon& operator=(const Pokemon& rhs){
      std::cout << "assign" << std::endl;
      if( this == &rhs ) {
        return *this;
      }

      delete [] name;

      name = new char[strlen(rhs.name) + 1];
      strcpy(name, rhs.name);

      index = rhs.index;
      ad = rhs.ad;
      defense = rhs.defense;
      hp = rhs.hp;

      return *this;
    }

    // getter functions
    const char* getName() const { return name; }
    int getIndex() const { return index; }
    int getAD() const { return ad; }
    int getDefense() const { return defense; }
    int getHP() const { return hp; }

private:
  char* name;
  int index;
  int ad;
  int defense;
  int hp;
};

// output override
std::ostream& operator<<( std::ostream& out, const Pokemon& p ){
  out << p.getName() << " - index: " << p.getIndex() << " ad: " << p.getAD()
    << " defense: " << p.getDefense() << " hp: " << p.getHP();
  return out;
}

int main() {
  Pokemon weedle;
  Pokemon dragonite("Dragonite", 1, 700, 80, 1530), dratini = dragonite;
  weedle = dragonite;

  std::cout << weedle << std::endl;
  std::cout << dragonite << std::endl;
  std::cout << dratini << std::endl;
  return 0;
}
