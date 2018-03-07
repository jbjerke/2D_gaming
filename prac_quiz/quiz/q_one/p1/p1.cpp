#include<iostream>

int cout = 45%7?5:0;
int endl = 7/2;

namespace Mine{
	namespace std{
		float cout = 2/4;
	}
}

int main(){
	std::cout << cout+endl << std::endl;
	std::cout << Mine::std::cout << std::endl;
}

