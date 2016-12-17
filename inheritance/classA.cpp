#include <iostream>


#ifndef A_H_
#define A_H_

class A{

 public:
   void A_init( int x_in ) ;
   ~A( void );
 
 private:
   int x ;

};


void A::A_init( int x_in ){

   x = x_in ;
   std::cout << "Class A " << std::endl ;
   std::cout << x << std ::endl;
}

A::~A( void ){

  std::cout << "Destructor" << std::endl;

}
#endif
