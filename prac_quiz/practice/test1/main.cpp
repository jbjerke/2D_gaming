#include<iostream>
#include<string>
#include<vector>

class Pokemon {
public:
	Pokemon( ) : name() {std::cout << "default" << std::endl;}
	Pokemon(const std::string& n) : name(n) {
		std::cout << "conversion" << std::endl;
	}
	Pokemon(const Pokemon& p) : name(p.name) {
		std::cout << "copy" << std::endl;
	}
	Pokemon& operator=(const Pokemon&) {
		std::cout << "copy" << std::endl;
		return *this;
	}
private:
	std::string name;
};

int main() {
	std::vector<Pokemon> pokes;
	pokes.reserve(2);
	pokes.push_back(std::string("Larvitar"));
	pokes.push_back(Pokemon("Steelix"));
	pokes.push_back(Pokemon("Dragonite"));
	std::cout << "size " << pokes.size() << std::endl;
	std::cout << "capacity " << pokes.capacity() << std::endl;
}
