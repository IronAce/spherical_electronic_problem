#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <complex>

#ifndef BASIS_SET_H
#include "basis_set.h"
#endif
#ifndef CONSTANTS_H
#include "consts.h"
#endif


  class calc_atom: spherical_harmonics { 

     public:
       calc_atom( int BSS_in , int Nx_in , int Ny_in , int Nz_in );
       ~calc_atom( void );
       void def_spherical_grid( double **& data , int Nx , int Ny , int Nz , double rmax ) ;
       void allocate_double_2d( double **& data , int N1 , int N2 ) ;
       void delete_double_2d( double **& data , int N1 );
       void basis_set_generator( void ) ;


     private:
       int          Nx ;                              //number of grid points x or r
       int          Ny ;                              //number of grid points y or theta
       int          Nz ;                              //number of grid points z or phi
       double       rmax = 100 ;                      //maximum value for r ( spherical coordinates )
       double    ** spher_grid ;                      //grid in spherical coordinates
       double    ** cart_grid ;                       //grid in cartesian coords
       std::complex<double> * wavefunction ;          //wavefunction
       int          BSS ;                             //Basis set size number of functions in basis set
       std::complex<double> ** spherical_basis_funcs; //basis functions             
       double **  bessel_radial_basis ;                //radial bessel basis
       int Ntheta ;                                   //theta grid points
       int Nphi ;                                     //phi grid points
       int Nr   ;                                     //radial grid points
       int NB;                                        //degree of highest bessel function

  };



  //****************************
  //    Class creator
  //***************************
  calc_atom::calc_atom( int BSS_in , int Nx_in , int Ny_in , int Nz_in ){
      
     Nx     =  Nx_in ;
     Ny     =  Ny_in ;
     Nz     =  Nz_in ;
     Nr     =  Nx_in ;
     Ntheta =  Ny_in ;
     Nphi   =  Nz_in ;
     BSS    =  BSS_in ;



     allocate_double_2d( spher_grid , Nx*Ny*Nz , 3 ) ;
     def_spherical_grid( spher_grid , Nx ,  Ny , Nz , rmax ) ;
     basis_set_generator();

  }



  //#####################################
  //  Calculate basis set 
  //#####################################
  void calc_atom::basis_set_generator( void ){
   
     double * r ;
     double * bessel_temp ;
     int l;
     std::ofstream file;
     void compute_bessel( double *& bessel_temp , int n , double *& x , int size ) ;


     r = new double [ Nr ] ;
     bessel_temp = new double [ Nr ] ;

    l = 0;
    for ( int i = 0 ; i < Nr ; i++ ){
      for ( int j = 0 ; j < Ntheta ; j++ ){
        for ( int k = 0 ; k < Nphi ; k ++ ){
           l += 1 ;
        }
      }
      r[ i ]  =  spher_grid[ l - 1 ][ 0 ];
    }



     spherical_harmonics basis;
     NB  =  BSS;
     basis.spherical_harmonics_init( BSS , Ntheta , Nphi ) ;

     spherical_basis_funcs  =  new std::complex<double> * [ Nphi * Ntheta ] ;

     for ( int i = 0 ; i < Nphi*Ntheta ; i++ ){
        spherical_basis_funcs[ i ]  =  new  std::complex<double> [ BSS ] ;
     }

     basis.return_basis( spherical_basis_funcs );
     basis.del_spherical_harmonics();
     
     std::cout << "**************************************************" << std::endl;
     std::cout << "Defining Bessel radial basis " << std::endl;
     //Determing radial bessel basis

     allocate_double_2d( bessel_radial_basis , Nr , NB ) ;

     for ( int n = 0 ; n < NB ; n++ ){
         compute_bessel( bessel_temp , n , r , Nr ) ;
         for ( int i = 0 ; i < Nr ; i++ ){
            bessel_radial_basis[ i ][ n ]  =  bessel_temp[ i ] ;
         }
     }

   //Writing Bessel functions to file
   file.open( "bessel_basis.out" );
   for ( int i = 0 ; i < Nr ; i++ ){
        file << r[ i ] << "   " ;
      for ( int j = 0 ; j < NB ; j++ ){
        file << bessel_radial_basis[ i ][ j ] << "   ";
      }
        file << std::endl;
   }

   std::cout << "**************************************************" <<std::endl;
   delete [ ] r ;
   r = 0;
   delete [] bessel_temp ;
   bessel_temp = 0;
  }



  //######################################
  //    Allocate Double array
  //######################################
  void calc_atom::allocate_double_2d( double **& data , int N1 , int N2 ){
 
    data =  new double * [ N1 ] ;
    for ( int i = 0 ; i < N1 ; i++ ){
      data[ i ] = new double [ N2 ] ;
    }
  }



  //######################################
  //      Class Destructor
  //######################################
  calc_atom::~calc_atom( void ){
     printf("********************************");
     printf("\n");
     printf( "Deleting generated arrays and then it is done \n" ); 
     delete_double_2d( spher_grid , Nx * Ny * Nz );
     printf( " Done ;-) \n" ) ;
     printf("\n");
  }


 
  //######################################
  // Delete a 2 dimensional double array
  //######################################
  void calc_atom::delete_double_2d( double **& data , int N1 ){
    for ( int i = 0 ; i < N1 ; i++ ){
       delete [ ] data[ i ] ;
    }
   delete [ ] data ;
   data = 0 ;
 
  }
  //######################################


 
 
  //######################################
  // Calculate grid in spherical coordinates
  //######################################
 
  void calc_atom::def_spherical_grid( double **& data , int Nphi , int Ntheta , int Nr , double rmax ){
   
    double pi = 2.0 * acos( 0.0 ) ;
    double dtheta ;
    double dphi ;
    double dr ;
    double theta;
    double phi ;
    double r ;
    int row ; 
 
    dtheta  =   pi / ( ( double ) ( Ntheta - 1 ) ) ;
    dphi    =   ( 2.0 * pi ) / ( ( double ) ( Nphi - 1 ) ) ;
    dr      =   rmax  / ( double ) ( Nr - 1 ) ;
 
 
    row = 0 ;
    for ( int i = 0 ; i < Nr ; i++ ){
      r  =  dr * ( double ) i + dr / 2.0;
      for ( int j = 0 ; j < Ntheta ; j++ ){
        theta  =  dtheta * ( double ) j + dtheta / 2.0 ;
        for ( int k = 0 ; k < Nphi ; k++ ){
          phi  =  dphi * ( double ) j + dphi / 2.0 ;
          data[ row ][ 0 ]  =  r ;
          data[ row ][ 1 ]  =  theta;
          data[ row ][ 2 ]  =  phi ;
          row++;
        }
      }
    }
  }
  //######################################


 

  int main(){

   calc_atom x( 10 , 100 , 50 , 100 );
   int a;



  }
