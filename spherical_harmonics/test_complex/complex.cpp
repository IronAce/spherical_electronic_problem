#include <iostream>
#include <complex>
#include <fstream>
#include <math.h>
#include <cmath>



int main(){

 const std::complex<double> imagi ( 0 , 1 ) ;
 std::complex<double> ** data ;
 double * grid1 ;
 double * grid2 ;
 int N1 ;
 int N2 ;
 double lower ;
 double upper ;
 double dx1 ;
 double dx2 ;
 std::ofstream file;

 N1       =  100;
 N2       =   50;
 lower   =  0.0 ;
 upper   =  4.0 * acos( 0.0 ) ;
 dx1  = ( upper - lower ) / ( double ) N1 ;
 dx2  = ( 2.0 * acos(0.0 ) ) / ( double ) N2 ;

 grid1    =  new double [ N1 ] ;
 grid2    =  new double [ N2 ] ;
 data    =  new std::complex<double> * [ N1 ] ;

 for ( int i = 0 ; i < N1 ; i++ ){
   grid1[ i ]  =  lower + dx1 * ( double ) i - dx1 / 2.0 ;
   data[ i ]   =  new std::complex<double> [ N2 ] ;
 } 

 for ( int i = 0 ; i < N2 ; i++ ){
   grid2[ i ] = dx2 * ( double ) i + dx2 / 2.0 ;
 }


 std::cout << "Printing fucking complex " << imagi << std::endl ; 

 for ( int i = 0 ; i < N1 ; i++ ){
   for ( int j = 0 ; j < N2 ; j++ ){
   //data[ i ]  =  exp( imagi * (std::complex<double>) grid[ i ] ) ;
      data[ i ][ j ]  =  exp( imagi * ( double ) 3 * grid1[ i ] ) * cos( grid2[ j ] ) ;
   }
 }

 file.open( "data.out" ) ;
   for ( int i = 0 ; i < N1 ; i++ ){
     for ( int j = 0 ; j < N2 ; j++ ){
        file << grid1[ i ] << "   "  << grid2[ j ] << "   " << real( data[ i ][ j ] ) << "   " << imag( data[ i ][ j ] ) << std::endl ;
     }
     file << std::endl ;
   }
 file.close();

 delete [ ] grid1 ;
 grid1 = 0;
 delete [ ] grid2 ;
 grid2 = 0;

 for ( int i = 0 ; i < N1 ; i++ ){
   delete[] data[ i ] ;
 }


 delete [ ] data ;
 data = 0;
}
