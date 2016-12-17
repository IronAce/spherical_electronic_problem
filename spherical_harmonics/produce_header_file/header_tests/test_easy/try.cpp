#include <iostream>
#include <math.h>

class header_class{

 public:
   header_class( void ) ;
   ~header_class( void ) ;
   void sum( void ) ;
 private:
   int a = 5;
   int b = 7;


};


header_class::header_class( void ){

  std::cout << std::endl ;
  std::cout << "I here you knocking" << std::endl ;
  std::cout << std::endl ;
}


header_class::~header_class( void ){

  std::cout << std::endl ;
  std::cout << "You killed me, Uhhh!" << std::endl ;
  std::cout << std::endl ;

}

void header_class::sum( void ){

  std::cout << std::endl ;
  std::cout << "The sum of your private variables is:  " << a + b << std::endl ;
  std::cout << "The sqrt of the sum is :               " << sqrt( ( double ) a + b ) ;
  std::cout << std::endl ;

}


int main(){

 header_class x;
 x.sum( );

}
