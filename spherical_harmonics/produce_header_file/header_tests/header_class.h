#include <iostream>
#include <math.h>

class Header_Class{

 public:
   Header_Class( void ) ;
   ~Header_Class( void ) ;
   void sum( void ) ;
 private:
   const int a = 4 ;
   const int b = 10 ;

};


Header_Class::Header_Class( void ){

  std::cout << std::endl ;
  std::cout << "I here you knocking" << std::endl ;
  std::cout << std::endl ;

}


Header_Class::~Header_Class( void ){

 std::cout << std::endl ;
 std::cout << "You killed me, Uhhh!" << std::endl ;
 std::cout << std::endl ;

}

void Header_Class::sum( void ){

  std::cout << std::endl ;
  std::cout << "The sum of your private variables is:  " << a + b << std::endl ;
  std::cout << "The sqrt of the sum is :               " << sqrt( ( double ) a + b ) ;
  std::cout << std::endl ;

}

