#include <math.h>
#include "nutril.h"
#define EPS      1.0e-16
#define FPMIN    1.0e-30
#define MAXIT    10000
#define XMIN     2.0

#ifndef CONSTANTS_H
#include "consts.h"
#endif



  void bessjy( double x , double xnu , double *rj , double *ry , double * rjp , double * ryp ){
   /* This routine will calculate the bessel 
      function of first and second kind 
      rj = J_{v} and ry = Y_{v} respectively; 
      the corresponding derivatives are given in 
      rjp = J_{v}^{'} and ryp = J_{v}^{'} ;
      x > 0 ; and xnu = v >= 0 
      the accuracy is determined by EPS;
      FPMIN is a number close to the machines 
      smallest floating point number*/
      










  }

  void cheb_pol( double x , double * gam1 , double *gam2 , double *gampl , double * gammi ){
    /*
     This routine calculates the Gamma1 Gamma2 by
     the chebychev expansion

    */





  }




































 /**************************************

    Computes Bessel function of degree n

 ***************************************/

/*  void compute_bessel( double *& bessel , int n , double *& x , int size ){

     long int factorial( int n ) ;

     for ( int i = 0 ; i < size ; i++ ){
        bessel[ i ]  =  0.0;
        for ( int m = 0 ; m < 30 ; m++ ){
           bessel[ i ] +=  ( pow( -1.0 , ( double ) m ) * pow( x[ i ] / 2.0  , ( double ) m + ( double ) n ) ) / 
                           ( ( double ) factorial( m ) * ( double ) factorial( n + m ) ) ;
        }     
     }
  } 

 */

 void spherical_bessel( int n , double *& x , double * sj , double * sy , double *sjp , double * syp ){

 





 /*USe numerical recipes for the calcultaion of the spherical bessel functions
   the comutation of those thingies is not so trivial as assumed because the first choosen
   method does not satisgy the frequency relation correctly
   On page of the Numerical Recipes in C book has to be considered closely
   before starting 



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
