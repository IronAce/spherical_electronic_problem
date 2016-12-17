#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>

  int main(){

     double ** x ;
     double * func ;
     double * func_prime ;
     double * func_prime2 ;
     int Nx ;
     int Ny ;
     double dtheta ; 
     double dphi ;
     int row ; 
     double theta ;
     double phi ;
     void function( double *& func , double **& x , int N ) ;
     void derivative_2d( double *& func , double delta1 , double delta2 , int Nx , int Ny , double *& result );
     std::ofstream file ;
     std::clock_t clock();
     double t1 ;
     double t2 ;

     t1  =  clock();

//     Nx   =   1000 
//     Ny   =   1000 ;
     std::cout << " Insert number of grid points x " << std::endl ;
     std::cin >> Nx ;
     std::cout << " Insert number of grid points y " << std::endl ;
     std::cin >> Ny ;

     row  =      0 ;

     dphi    =  ( 4.0 * acos( 0.0 ) ) / ( double ) Nx  ;
     dtheta  =  ( 2.0 * acos( 0.0 ) ) / ( double ) Ny  ;
 
     func         =  new double [ Nx * Ny ] ;
     func_prime   =  new double [ Nx * Ny ] ;
     func_prime2  =  new double [ Nx * Ny ] ;
    


     x = new double * [ Nx * Ny ] ;
     for ( int i = 0 ; i < Nx * Ny ; i++ ){
        x[ i ]  =  new double [ 2 ] ;
     }

     for ( int i = 0 ; i < Ny ; i++ ){
        theta   =   ( double ) i * dtheta + dtheta / 2.0 ;
        for ( int j = 0 ; j < Nx ; j++ ){
            phi  =  ( double ) j * dphi + dphi / 2.0 ;
            x[ row ][ 0 ] = theta ;
            x[ row ][ 1 ] = phi ;
            row ++ ;
        }
     }

    std::cout << "Boundaries " << std::endl ;
    std::cout << "x values " << std::endl;
    std::cout << x[ 0 ][ 0 ] << "   "  << x[ Nx * Ny - 1 ][ 0 ] << std::endl;
    std::cout << "y values " << std::endl;
    std::cout << x[ 0 ][ 1 ] << "   "  << x[ Nx * Ny - 1 ][ 1 ] << std::endl;



    function( func , x , Nx * Ny ) ;

    derivative_2d( func , dtheta , dphi , Ny , Nx , func_prime ); 
    derivative_2d( func_prime , dtheta , dphi , Ny , Nx , func_prime2 ); 
    file.open("test.dat") ;


    for ( int i = 0 ; i < Nx * Ny ; i++ ){
       file << x[ i ][ 0 ]  <<  "   "  <<  x[ i ][ 1 ]  <<  "   " << func[ i ] 
            << "   " << func_prime[ i ] << "   " << func_prime2[ i ]  << std::endl;
    }


     for ( int i = 0 ; i < Nx * Ny ; i++ ){
       delete [ ] x[ i ] ;
     }

     delete [ ] x ;
     x = 0;
     delete [ ] func ;
     delete [ ] func_prime ;
     delete [ ] func_prime2;
     func        = 0 ;
     func_prime  = 0 ;
     func_prime2 = 0 ;

     t2  =  clock();
     std::cout << std::endl;
     std::cout << "Integration duration for " << std::endl;
     std::cout << Nx * Ny << "   " << "grid points " << std::endl;
     std::cout << ( t2 - t1 ) / CLOCKS_PER_SEC << std::endl ;
     std::cout << std::endl;

  } 

  /******************************************************

         Function definition

  *******************************************************/
  void function( double *& func , double **& x , int N ){

    for ( int i = 0 ; i < N ; i++ ){
       func[ i ]  =  sin( x[ i ][ 0 ] ) * cos( x[ i ][ 1 ] ) ;
    }
  }
