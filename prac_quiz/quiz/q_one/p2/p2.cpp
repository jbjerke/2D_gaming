#include<iostream>

class Pokemon{
public:
	Pokemon() : cp(0) { std::cout<< "Default" << std::endl; }
	Pokemon(int p) : cp(p) { std::cout<< "convert" <<std::endl;}
	Pokemon(const Pokemon& p) : cp(p.cp) { std::cout<< "copy" << std::endl; }
	Pokemon& operator=(const Pokemon&) {
		std::cout << "assign" << std::endl;
		return *this;
	}
	
private:
	int cp;
};

class Pokedex { 
public:
	Pokedex(const Pokemon& p) {mon = p;}
private:
	Pokemon mon;
};

int main() {
	Pokedex dex(2750);
}
