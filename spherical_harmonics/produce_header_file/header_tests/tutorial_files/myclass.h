#include <iostream>

class MyClass
{
public:
  MyClass( void );
  ~MyClass( void );
  void foo();
  int bar;
};

MyClass::MyClass( void ){
  std::cout << std::endl ;
}

MyClass::~MyClass( void ){

}

void MyClass::foo()
{
 std::cout << std::endl;
}
