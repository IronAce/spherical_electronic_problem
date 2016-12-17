#include <math.h>


 /**************************************

    Computes Bessel function of degree n

 ***************************************/

  void compute_bessel( double *& bessel , int n , double *& x , int size ){

     long int factorial( int n ) ;

     for ( int i = 0 ; i < size ; i++ ){
        bessel[ i ]  =  0.0;
        for ( int m = 0 ; m < 20 ; m++ ){
           bessel[ i ] +=  ( pow( -1.0 , ( double ) m ) * pow( x[ i ] / 2.0  , ( double ) m + ( double ) n ) ) / 
                           ( ( double ) factorial( m ) * ( double ) factorial( n + m ) ) ;
        }     
     }
  } 

  /*************************************

   Computes the factorial of a function
  
  *************************************/
  long int factorial( int n ){

       long int result;

       result = 1 ;
       for ( int i = 1 ; i <= n ; i++ ){
           result *= i ;
       }

       return result ;
  }
