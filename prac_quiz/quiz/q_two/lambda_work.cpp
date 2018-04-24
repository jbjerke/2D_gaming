#include <iostream>
#include <functional>
#include <ctime>

int main() {
  srand( time(0) );
  int speed = rand() % 100;

  speed = speed * (rand()%2?-1:1);
  std::cout<<"speed" << speed << std::endl;

  auto fixSpeed = [](){ return rand()%2?-1:1; };
  speed = speed * fixSpeed();
  std::cout << "speed" << speed << std::endl;

  int number = rand() % 100;
  std::cout << "number" << number << std::endl;
  auto isEven = [](int n){ return n%2?0:1; };
  std::cout << "isEven(number) = " << isEven(number) << std::endl;
}
