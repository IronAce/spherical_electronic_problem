#include <iostream>
#include <math.h> 
#include <stdio.h>
#include "fun.h"


int main(){

 double * x ;
 int N = 10 ;
 void func( double *& , int ) ;

 x = new double [ N ] ;

 for ( int i = 0 ; i < N ; i++ ){
   x[ i ] = ( double ) i ;
 }

 func( x , N );

 for ( int i = 0 ; i < N ; i++ ){
    printf( " %4.2f \n " , x[ i ] );
 } 
}
