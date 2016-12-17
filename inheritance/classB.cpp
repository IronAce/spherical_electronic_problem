

#ifndef A_H_
#include "classA.cpp"
#endif

class B: public A {

  public:
    B( void ) ;
    //A( int x_in ) ;

};

B::B( void ){
 std::cout << std::endl; 
 A x;
 x.A_init( 5 );
 x.~A();

 x.A_init( 7 );

 std::cout << "HERERERER" << std::endl;
}



int main(){

 B x;

}
