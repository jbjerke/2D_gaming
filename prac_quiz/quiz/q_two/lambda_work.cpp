#include <iostream>
#include <functional>
#include <ctime>

int main() {
  srand( time(0) );
  int speed = rand() % 100;

  speed = speed * (rand()%2?-1:1);
  std::cout<<"speed" << speed << std::endl;

  //lambda here
  speed = speed * fixSpeed();
  std::cout << "speed" << speed << std::endl;

  int number = rand() % 100;
  std::cout << "number" << number << std::endl;
  // lambda here
  std::cout << "isEven(number) = " << isEven(number) << std::endl;
}
