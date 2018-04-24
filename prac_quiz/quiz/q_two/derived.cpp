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
  Derived& operator=(const Derived& d){
    if( this == &d ) return *this;

    delete name;
    name = new char[strlen(d.getName())+1];
    strcpy(name, d.getName());
    return *this;
  }
  const char* getName() const { return name; }

private:
  char * name;
};

int main() {
  Derived d("bill"), e;
  e = d;
  std::cout<<e.getName()<<std::endl;
}
