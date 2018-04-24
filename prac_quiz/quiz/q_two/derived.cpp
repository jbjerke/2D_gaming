#include <iostream>
#include <cstring>

class Base{ };

class Derived : public Base {
public:
  Derived() : name(new char[1]){
    name[0] = '\0';
  }
  Derived(const char* n) : name(new char[strlen(n)+1]){
    strcpy(name, n);
  }
  //overload
  const char* getName() const { return name; }

private:
  char * name;
};

int main() {
  Derived d("bill"), e;
  e = d;
  std::cout<<e.getName()<<std::endl;
}
