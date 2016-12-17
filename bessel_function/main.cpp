#include <iostream>
#include <fstream>
#include <math.h>

int main(){

  int size ;
  double ** bessel ;
  double * bessel_temp ;
  double * x ;
  int n ;
  double dx ;
  std::ofstream file;
  void compute_bessel( double *& bessel , int n , double *& x , int size ) ;


  size  =  50;
  dx    =  20.0 / ( double ) size ;
  
  x            =   new double [ size ] ;
  bessel_temp  =   new double [ size ] ;
  bessel       =   new double * [ size ] ;

  n = 10 ;

  for ( int i = 0 ; i < size ; i++ ){
     bessel[ i ]  =  new double [ n ] ;
  }


  for ( int i = 0 ; i < size ; i++ ){
    x[ i ]  =  dx * ( double ) i + dx / 2.0 ;
  }
  

  file.open( "bessel.out" ) ;
  
  for ( int i = 0 ; i < n ; i++ ){
     compute_bessel( bessel_temp , i , x , size ) ;
     for ( int j = 0 ; j < size ; j++ ){
        bessel[ j ][ i ]  =  bessel_temp[ j ] ;
     } 
  }


  for ( int i = 0 ; i < size ; i++ ){
     file << x[ i ] << "   " ;
     for ( int j = 0 ; j < n ; j++ ){
       file << bessel[ i ][ j ] << "  " ;

     }
     file << std::endl ;
  }




  file.close() ;

  delete [ ] bessel_temp ;
  bessel_temp = 0 ;

  for ( int i = 0 ; i < size ; i ++){
     delete [ ]  bessel[ i ] ;
  }

  delete [ ] bessel ;
  bessel = 0 ;


}
