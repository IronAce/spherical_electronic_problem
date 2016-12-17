#include <iostream>



class test_class{

 public:
  test_class( int Nin ) ; 
  ~test_class( void ) ;
  void get_data( double *& datain ) ;

 private:
 double * data ;
 int N ;



};


test_class::test_class( int Nin ){

 std::cout << " Check input " << std::endl ;
 N = Nin; 
 std::cout << N << std::endl ;
 data  =  new double [ N ] ;

}

void test_class::get_data( double *& datain ){
 
 std::cout << " Checking data again " << std::endl;
 std::cout << "N  " <<  N  << std::endl ;

 for ( int i = 0 ; i < N ; i++ ){
   std::cout  <<  datain[ i ]  <<  std::endl ;
   data[ i ]  =  datain[ i ] ;
   data[ i ]  =  data[ i ] * 2.0 ;
   datain[ i ] = data[ i ] ;

 }


}



test_class::~test_class( void ){

  delete [] data ;
  data = 0 ;
}



int main(){

  double * x ;
  int N = 100;
  test_class y( N ) ;

  x = new double [ N ] ;


  for ( int i = 0 ; i < N ; i++ ){
    x[ i ] = ( double ) i ;
  }

  y.get_data( x ) ;
  std::cout << " Back values hopefully twice as large " << std::endl ;
  for ( int i = 0 ; i < N ; i++ ){
    std::cout << x[ i ] << std::endl ;
  }


  delete [ ] x;
  x = 0;

}
