#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
#include <time.h>


int main(){

 
  double              ** legendre_pols ;
  std::complex<double>              ** spherical_harm ;
  double               * legendre_temp ;
  double               *  grid ;
  double               *  phi ;
  double               *  cos_grid ;
  int                     N ;
  int                     N2 ;
  int                     col ;
  clock_t                 time ; 
  void det_grid( double *& grid , int N , double lower , double upper ) ;
  void det_cos_grid( double *& grid , double *& cos_grid , int N ) ;
  void calc_legendre( int l , int m , double *& x , double *& result , int N ) ; 
  void write( double * x , double ** data , int N , int M );
  void spherical_harm_calc( std::complex<double> **& spherical_harm , double *& phi , double **& legendre , int Ntheta , int Nphi );
  void write_complex( double * x , double * y , std::complex<double> ** data , int N , int N2 , int M );
 
  void double_matrix( double * x , int N ); 

  time = clock( ) ;


  N   = 50 ;
  N2  = 100 ;


  grid             =  new double [ N ] ;
  phi              =  new double [ N2 ] ;
  cos_grid         =  new double [ N ] ;
  legendre_temp    =  new double [ N ] ;
  legendre_pols    =  new double * [ N ] ;
  spherical_harm   =  new std::complex<double> * [ N * N2 ] ;

  for ( int i = 0 ; i < N ; i++ ){
    legendre_pols[ i ]  =  new double [ 100 ] ;
  }

  for ( int i = 0 ; i < N * N2 ; i++ ){
    spherical_harm[ i ]  =  new std::complex<double> [ 100 ] ;
  }

  det_grid( grid , N , 0.0 , 2.0 * acos( 0.0 ) ) ;
  det_grid( phi , N2 , 0.0 , 4.0 * acos( 0.0 ) ) ;
  det_cos_grid( grid , cos_grid , N ) ; 


  col = 0 ; 
  for ( int l = 0 ; l < 10 ; l++ ){
    for ( int m = 0 ; m <= l ; m++ ){
       calc_legendre( l , m , cos_grid , legendre_temp , N ) ;
       for ( int i = 0 ; i < N ; i++ ){
          legendre_pols[ i ][ col ]  =  legendre_temp[ i ] ;
       }
       col++ ;
    }
  }


  spherical_harm_calc( spherical_harm , phi , legendre_pols , N , N2 ) ;

  write( cos_grid , legendre_pols , N , 10 );
  write_complex( grid , phi , spherical_harm , N , N2 , 10 );

  //double_matrix( phi , N2 ); 

  time = clock() - time ;

  std :: cout << " Calculation time " <<  ( float ) time / CLOCKS_PER_SEC << std::endl;

}


void double_matrix( double * x , int N ){

  const std::complex<double> imag ( 0 , 1 );
  std::ofstream file ; 
  std::complex<double> value ;

  file.open( "test_file.out" ) ; 


  for ( int i = 0 ; i < N ; i++ ){
      value = exp( imag * x[ i ] ) ;
      file << x[ i ] << "   "  <<  real( value ) ;
      file << std::endl ;
  }
 

  file.close() ;

}


//**********************************************
//      Write complex array to file 
//**********************************************

void write_complex( double * x , double * y , std::complex<double> ** data , int N , int N2 , int M ){

 std::ofstream file ; 

 file.open( "spherical_harmonics.out" ) ; 



  for ( int i = 0 ; i < N ; i++ ){
    //file << x[ i ] << "   " ;
    for ( int k = 0 ; k < N2 ; k++ ){
      file << x[ i ] << "    " << y[ k ] << "   " ; 
      for ( int j = 0 ; j < M ; j++ ){
        file << real( data[ i ][ j ] ) << "   " << imag( data[ i ][ j ] );
        file << "    ";
      }
      file << std::endl ;   
    }
    file << std::endl ;
  }
 file.close( ) ;

}

 
//**********************************************
//           Calculte spherical harmonic 
//**********************************************
void spherical_harm_calc( std::complex<double> **& spherical_harm , double *& phi , double **& legendre , int Ntheta , int Nphi ){

 int col = 0 ; 
 int row ; 
 double norm ;
 double calc_norm( int l , int m ) ;
 const std::complex<double> imagi ( 0 , 1 );
 


 for ( int l = 0 ; l < 10 ; l++ ){
   for ( int m = 0 ; m <= l ; m++ ){
     norm  =  calc_norm( l , m ) ;
     std::cout << norm << std::endl;
     row   = 0 ; 
     for ( int i = 0 ; i < Ntheta ; i++ ){
       for ( int j = 0 ; j < Nphi ; j++ ){
           std::cout << real( norm * exp( imagi * ( double ) m * phi[ j ] ) ) << "   " << imag( norm * exp( imagi * ( double ) m * phi[ j ] ) ) << std::endl;
           spherical_harm[ row ][ col ]  =  norm * exp( imagi * ( double ) m * phi[ j ] ) * legendre[ i ][ col ];
           row++ ;
       }
     }
   }
   col++ ;
 }
}
//**********************************************
//      Write array to file 
//**********************************************


void write( double * x , double ** data , int N , int M ){

 std::ofstream file ; 

 file.open( "legendre_pols.out" ) ; 



  for ( int i = 0 ; i < N ; i++ ){
    file << x[ i ] << "  " ;
    for ( int j = 0 ; j < M ; j++ ){
       file << data[ i ][ j ] ;
       file << "    ";
    }
       file << std::endl ;
  }
 file.close( ) ;

}


//**********************************************
//       Calculate legendre polynomials 
//**********************************************
void calc_legendre( int l , int m , double *& x , double*& result , int N ){


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
//           Determine grid
//**********************************************
void det_grid( double *& grid , int N , double lower , double upper ){

 double dx ; 


 dx      = ( upper - lower ) / ( double ) N;

 for ( int i = 0 ; i <= N ; i++ ){
    grid[ i ]  =  lower + dx * ( double ) ( i + 1 ) - dx * 0.5 ; 
 }

}


//**********************************************
//    Calc cos grid
//**********************************************
void det_cos_grid( double *& grid , double *& cos_grid , int N ){

  for ( int i = 0 ; i < N ; i++ ){
    cos_grid[ i ]  =  cos( grid[ i ] ) ;
  }

}

//**********************************************
//  Calculating norm for spherical harmonics
//**********************************************

double calc_norm( int l , int m ){

 unsigned int t1 ; 
 unsigned int t2 ;
 double result ;
 double pi = 2.0 * acos( 0.0 ) ; 



 t1 = 1 ;
 t2 = 1 ;

 for ( int i = 1 ; i < l - m ; i++ ){
   t1 = t1 * i ;
 }


 for ( int i = 1 ; i < l + m ; i++ ){
   t2 = t2 * i ;
 }

 //std::cout << t1 << "  " << t2 << std::endl;


 result  =  sqrt( ( ( 2.0 * ( double ) l + 1.0 ) / ( 4.0 * pi ) ) * ( ( double ) t1 / ( double ) t2 ) ) ;
 
 return result ;

}
