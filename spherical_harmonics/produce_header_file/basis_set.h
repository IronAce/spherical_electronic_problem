#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>

#ifndef CONSTANTS_H
#include "consts.h"
#endif

#ifndef BASIS_SET_H
#define BASIS_SET_H
class spherical_harmonics: public constants {

  public:
    spherical_harmonics( int & lmax_in , int Ntheta_in , int Nphi_in );
    int basis_set_size( void ) ;
    ~spherical_harmonics( void ) ;
    void det_grid( double *& grid , int N , double lower , double upper ) ;
    void det_cos_grid( double *& grid , double *& cos_grid , int N ) ;
    void calc_legendre( int l , int m , double *& x , double*& result , int N );
    double calc_norm( int l , int m ) ;
    void spherical_harm_calc( void ) ; 
    void calc_basis_set( void ) ;
    double m_norm( int l , int m );
    void return_basis( std::complex<double> **& results ) ;



  private:
    double                ** legendre_pols ;         //array for storing needeed legendres
    std::complex<double>  ** spherical_harm ;        //sherical harmonic storage
    double                *  legendre_temp ;          //temporrary array for calculating legendres
    double                *  theta ;                 //theta grid
    double                *  cos_theta ;             //cos theta grid
    double                *  phi ;                   //phi grid
    int                      Ntheta ;                //number theta grid points
    int                      Nphi ;                  //number of phi grid points
    int                      angular_l ;             //angular momentum quantum number ( parameter for spherical harmonics calc )
    int                      angular_lmax ;          //angular momentum quantum number max ( parameter for spherical harmonics calc )
    int                      Nfunctions;             //Number of resulting functions
};

/***********************************************
 
      Class Creator

************************************************/
spherical_harmonics::spherical_harmonics( int & lmax_in , int Ntheta_in , int Nphi_in ){

 std::cout << std::endl ;
 std::cout << "*************************************************" << std::endl ;
 std::cout << std::endl ;
 std::cout << "Starting the calculation of the spherical harmonic basis set" << std::endl;
 std::cout << "A value lmax of " << lmax_in << " was given and " << std::endl;

 //passing variables
 Ntheta         =  Ntheta_in ;
 Nphi           =  Nphi_in ;
 angular_lmax   =  lmax_in ;
 Nfunctions     =  basis_set_size( ) ;

 lmax_in = Nfunctions ;

 std::cout << "therefore the basis set will consist of " << Nfunctions << " functions" << std::endl;
 

 //Allocating arrays
 theta          =  new double [ Ntheta ] ;
 cos_theta      =  new double [ Ntheta ] ;
 phi            =  new double [ Nphi ] ;

 legendre_temp  =  new double [ Ntheta ] ;

 legendre_pols  =  new double * [ Ntheta ] ;
 for ( int i = 0 ; i < Ntheta ; i++ ){
    legendre_pols[ i ]  =  new  double [ Nfunctions ] ;
 }
 
 spherical_harm  =  new std::complex<double> * [ Nphi * Ntheta ] ;
 for ( int i = 0 ; i < Nphi * Ntheta ; i++ ){
    spherical_harm[ i ]  =  new std::complex<double> [ Nfunctions ] ;
 }
 //___________________________________________________



 // Grids used in current computation
 std::cout << " Determining grids " << std::endl; 
 det_grid( theta , Ntheta , 0.0 ,  pi ) ;
 det_grid( phi , Nphi , 0.0 ,  2.0 * pi ) ;
 det_cos_grid( theta , cos_theta , Ntheta ) ;
 std::cout << " Grids determined " << std::endl;
 calc_basis_set();
 
}

/*****************************************************

  Cleaning up after calculation

******************************************************/
spherical_harmonics::~spherical_harmonics( void ){

 std::cout << std::endl ;
 std::cout << "Basis set successfully calculated " << std::endl;
 std::cout << "Doing clean up after computing basis set " << std::endl;
 delete [ ] theta ;
 theta =   0 ;
 delete [ ] phi ;
 phi   =   0 ;
 delete [ ] cos_theta ;
 cos_theta = 0 ;

 for ( int i = 0 ; i < Ntheta ; i++ ){
    delete [ ] legendre_pols[ i ] ; 
 }
 delete [ ] legendre_pols ;
 legendre_pols  =  0 ;

 for ( int i = 0 ; i < Ntheta * Nphi ; i++ ){
    delete [ ] spherical_harm[ i ] ;
 }
 delete [ ] spherical_harm ;
 spherical_harm  =  0 ;


 std::cout << "***********************************************" << std::endl;
 std::cout << std::endl ;


}
/****************************************************************************

   Determining size of basis set ( number of functions 2l+1 per value of l )

*****************************************************************************/
int spherical_harmonics::basis_set_size( void ){

   int amx ;  //just a shitty name for a temporrary variable

   amx = 1 ;
   for ( int i = 1 ; i <= angular_lmax ; i++ ){
     amx +=  ( 2 * i  + 1 ) ;
   }
   return amx ;
}


//**********************************************

//           Determine grid

//**********************************************
void spherical_harmonics::det_grid( double *& grid , int N , double lower , double upper ){

 double dx ;


 dx      = ( upper - lower ) / ( double ) N;

 for ( int i = 0 ; i <= N ; i++ ){
    grid[ i ]  =  lower + dx * ( double ) ( i + 1 ) - dx * 0.5 ;
 }

}


//**********************************************

//    Calc cos grid

//**********************************************
void spherical_harmonics::det_cos_grid( double *& grid , double *& cos_grid , int N ){

  for ( int i = 0 ; i < N ; i++ ){
    cos_grid[ i ]  =  cos( grid[ i ] ) ;
  }

}

//**********************************************

//  Calculating norm for spherical harmonics

//**********************************************

double spherical_harmonics::calc_norm( int l , int m ){

 unsigned int t1 ;
 unsigned int t2 ;
 double result ;
 double pi = 2.0 * acos( 0.0 ) ;



 t1 = 1 ;
 t2 = 1 ;

 //Calc ( l - m)! 
 for ( int i = 1 ; i <= l - m ; i++ ){
   t1 = t1 * i ;
 }


 //Calc ( l + m)! 
 for ( int i = 1 ; i <= l + m ; i++ ){
   t2 = t2 * i ;
 }
 
 //srqt( ( 2l + 1 ) / 4pi * ( l - m )!/( l + m )! )
 result  =  sqrt( ( 2.0 * ( double ) l * ( double ) t1 + ( double ) t1 ) / ( 4.0 * pi * ( double ) t2 ) ) ;

 return result ;
}


//**********************************************

//       Calculate legendre polynomials 

//**********************************************
void spherical_harmonics::calc_legendre( int l , int m , double *& x , double*& result , int N ){


 double * Pmm ;
 double * PmmP1 ;
 double * T1  ;     //( 1 - x**2 )** 1 / 2
 double factor ; 
 double * Pll ;
 


 //Allocating nedded arrays 
 Pmm   =   new double [ N ] ; 
 T1    =   new double [ N ] ; 
 PmmP1 =   new double [ N ] ;
 Pll   =   new double [ N ] ;

 //Testing for correctness of arguments
 if ( m < 0 or m > l ){
   printf( "Value of m is out of range -l <= m <= l \n" ) ;
   exit( 1 );
 }
 for ( int i = 0 ; i < N ; i++ ){
    if ( abs( x[ i ] ) > 1 ){
      printf( "Given grid is not okay \n " ) ;
      exit( 1 ) ;
    }
 }

 // initialisation
 for ( int i = 0 ; i < N ; i++ ){
   Pmm[ i ]  = 1.0 ;
 }
//____________________________________________

  // Calculte P_{m}^{m}
  // 
 if ( m > 0 ){
    for ( int i = 0 ; i < N ; i++ ){
      T1[ i ]   =  sqrt( ( 1.0 - x[ i ] ) * ( 1.0 + x[ i ] ) ) ;
    }
    factor = 1.0 ;  

    for ( int i = 0 ; i < m ; i++ ){
       for ( int j = 0 ; j < N ; j++ ){
          Pmm[ j ]  =  - Pmm[ j ] * factor * T1[ j ] ;
       }
       factor += 2.0 ; 
    }
 }
 //
 if ( l == m ){
   for ( int i = 0 ; i < N ; i++ ){
      result[ i ]  =  Pmm[ i ] ;
   }
 }
 // Computing P_{ m + 1 }^{ m }
 else{
   for ( int i = 0 ; i < N ; i++ ){
     PmmP1[ i ]  =  x[ i ] * ( 2.0 * ( double ) m + 1.0 ) * Pmm[ i ] ;
   }
  
   if ( l == m + 1 ){
     for ( int i = 0 ; i < N ; i++ ){
        result[ i ]  =  PmmP1[ i ] ;
     }
   }
   else{
     for ( int ll = m + 2 ; ll <= l ; ll++ ){
       for ( int i = 0 ; i < N ; i++ ){
         Pll[ i ]   =  ( x[ i ] * ( 2.0 * ( double ) ll  - 1.0 ) * PmmP1[ i ] - ( ( double ) ll  + ( double ) m - 1.0 ) * Pmm[ i ] ) / ( ( double ) ll - ( double ) m );
         Pmm[ i ]   =  PmmP1[ i ] ;
         PmmP1[ i ] =  Pll[ i ] ; 
       }
     }
     for ( int i = 0 ; i < N ; i++ ){
       result[ i ]  =  Pll[ i ] ;
     }
   }
 }

}

//**********************************************

//           Calculte spherical harmonic 

//**********************************************

void spherical_harmonics::spherical_harm_calc( void ){

 int col = 0 ; 
 int row ; 
 double norm ;
 const std::complex<double> imagi ( 0 , 1 );
 
 //Calculate spherical harmonic by just multiplying associated legendres by e( i*phi )

 for ( int l = 0 ; l < 10 ; l++ ){
   for ( int m = 0 ; m <= l ; m++ ){
     norm  =  calc_norm( l , m ) ;
     row   = 0 ; 
     for ( int i = 0 ; i < Ntheta ; i++ ){
       for ( int j = 0 ; j < Nphi ; j++ ){
           spherical_harm[ row ][ col ]  =  norm * exp( imagi * ( double ) m * phi[ j ] ) * legendre_pols[ i ][ col ];
           row++ ;
       }
     }
   }
   col++ ;
 }

}

/**************************************************

   Calculate basis set

***************************************************/
void spherical_harmonics::calc_basis_set( void ){

 int col = 0;
 double t1 ;
 double t2 ;
 double factor ;


  for ( int l = 0; l < angular_lmax ; l++ ){
     for ( int m = 0 ; m <= l ; m++ ){
         calc_legendre( l , m , cos_theta , legendre_temp , Ntheta ) ;
        if ( m == 0 ){
           for ( int i = 0 ; i < Ntheta ; i++ ){
              legendre_pols[ i ][ col ]  =  legendre_temp[ i ] ;
           }
           col++;
        }
        else{
           for ( int i = 0 ; i < Ntheta ; i++ ){
              legendre_pols[ i ][ col ]  =  legendre_temp[ i ] ;
           }
           col++;
           factor =   m_norm( l , m ) ;
           factor *=  pow( ( -1.0 ) , m ) ;
           for ( int i = 0 ; i < Ntheta ; i++ ){
              legendre_pols[ i ][ col ]  =  legendre_temp[ i ] ;
           }
           col++; 
        }
     }
  }

  //Makes legendres to sphericals
  spherical_harm_calc() ;
}

/***************************************************

   Calculate transformation factor for legendres

****************************************************/
double spherical_harmonics::m_norm( int l , int m ){

  double t1 ;
  double t2 ;
  double result ;

  t1 = 1;
  for ( int i = 1 ; i <= l - m ; i++ ){
     t1  *=  ( double ) i ;
  }

  for ( int i = 1 ; i <= l + m ; i++ ){
     t2  *=  ( double ) i ;
  }

  result  =  t1 / t2 ;

}


/****************************************************

    Return basis set to main code

*****************************************************/

void spherical_harmonics::return_basis( std::complex<double> **& results ){

 int row ;
 std::ofstream file;
 file.open( "basis_set.out" ) ;

  for ( int i = 0 ; i < Ntheta * Nphi ; i++ ){
     for ( int j = 0 ; j < Nfunctions ; j++ ){
        results[ i ][ j ] = spherical_harm[ i ][ j ] ;
     }
  }

  row = 0 ;
  for ( int i = 0 ; i < Ntheta ; i++ ){
    //file << x[ i ] << "   " ;
    for ( int k = 0 ; k < Nphi ; k++ ){
      file << theta[ i ] << "    " << phi[ k ] << "   " ;
      for ( int j = 0 ; j < Nfunctions ; j++ ){
        file << real( spherical_harm[ row ][ j ] ) << "   " << imag( spherical_harm[ row ][ j ] );
        file << "    ";
      }
      file << std::endl ;
      row++;
    }
    file << std::endl ;
  }
 file.close( ) ;


}
#endif
