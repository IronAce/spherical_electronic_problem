#include <complex>
#include <iostream>
#ifndef CONSTANTS_H
#include "basis_set.h"
#endif

int main(){
 
 int N1 = 50 ;
 int N2 = 100 ;
 int NB = 3 ;
 std::complex<double> ** data;


 spherical_harmonics a( NB , N1 , N2 ) ;


 data  =  new std::complex<double> * [ N1*N2 ] ;
 for ( int i = 0 ; i < N1*N2 ; i++ ){
    data[ i ]  =  new std::complex<double> [ NB ] ;
 } 


 a.return_basis( data );

 std::cout << NB << std::endl ;

 for ( int i = 0 ; i < N1 * N2 ; i++ ){
   for ( int j = 0 ; j < NB ; j++ ){
     std::cout << data[ i ][ j ] << "   " ;
   }
   std::cout << std::endl;
 }





 return 0 ;
}

