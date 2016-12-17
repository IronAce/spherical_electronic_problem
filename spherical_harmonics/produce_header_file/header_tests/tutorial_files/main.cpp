//in main.cpp
#include <iostream>
#include "myclass.h"  // defines MyClass

int main()
{
  MyClass a; // no longer produces an error, because MyClass is defined
  a.foo();

  return 0;
}
