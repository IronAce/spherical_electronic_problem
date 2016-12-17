
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  void derivative_2d( double *& func , double delta1 , double delta2 , int Nx , int Ny , double *& result ){

     double ** work ;
     double ** work_result ;
     int entry ;
     double delta1_inv1 ;
     double delta2_inv1 ;
     double delta1_inv2 ;
     double delta2_inv2 ;

     work          =   new double * [ Nx ] ;
     work_result   =   new double * [ Nx ] ;

     for ( int i = 0 ; i < Nx ; i++ ){
       work[ i ]         = new double [ Ny ] ;
       work_result[ i ]  = new double [ Ny ] ;
     }

     entry = 0 ;
     for ( int i = 0 ; i < Nx ; i++ ){
        for ( int j = 0 ; j < Ny ; j++ ){
           work[ i ][ j ]  =  func[ entry ] ;
           entry++;
        }
     }

     //defining delta for bulk stuff
     delta1_inv2  =  1.0 / ( 2.0 * delta1 ) ;
     delta2_inv2  =  1.0 / ( 2.0 * delta2 ) ;
     delta1_inv1  =  1.0 / ( delta1 ) ;
     delta2_inv1  =  1.0 / ( delta2 ) ;


     //edges ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     work_result[ 0 ][ 0 ]             =  ( work[ 1 ][ 0 ]  -  work[ 0 ][ 0 ] ) * delta1_inv1
                                       +  ( work[ 0 ][ 1 ]  -  work[ 0 ][ 0 ] ) * delta2_inv1 ;
     work_result[ Nx - 1  ][ 0 ]       =  ( work[ Nx  - 1 ][ 0 ]  -  work[ Nx - 2 ][ 0 ] ) * delta1_inv1
                                       +  ( work[ Nx - 1 ][ 1 ]   -  work[ Nx - 1 ][ 0 ] ) * delta2_inv1 ;
     work_result[ 0 ][ Ny - 1 ]        =  ( work[ 1 ][ Ny - 1 ]  -  work[ 0 ][ Ny - 1 ] ) * delta1_inv1
                                       +  ( work[ 0 ][ Ny - 1 ]  -  work[ 0 ][ Ny - 2 ] ) * delta2_inv1 ;
     work_result[ Nx - 1 ][ Ny - 1 ]   =  ( work[ Nx - 1 ][ Ny - 1 ]  -  work[ Nx - 2 ][ Ny - 1 ] ) * delta1_inv1
                                       +  ( work[ Nx - 1 ][ Ny - 1 ]  -  work[ Nx - 1 ][ Ny - 2 ] ) * delta2_inv1 ;

     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

     //Walking along min_x and max_x ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     for ( int i = 1 ; i < Ny - 1 ; i++ ){
        work_result[ 0 ][ i ]       =   ( work[ 0 ][ i + 1 ] - work[ 0 ][ i - 1 ] ) * delta2_inv2
                                    +   ( work[ 1 ][ i ] - work[ 0 ][ i ] ) * delta1_inv1 ;
        work_result[ Nx - 1 ][ i ]  =   ( work[ Nx - 1 ][ i + 1 ] - work[ Nx - 1 ][ i - 1 ] ) * delta2_inv2
                                    +   ( work[ Nx - 1 ][ i ] - work[ Nx - 2 ][ i ] ) * delta1_inv1 ;
     }
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



     //Walking along min_y and max_y ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     for ( int i = 1 ; i < Nx - 1; i++ ){
        work_result[ i ][ 0 ]       =   ( work[ i + 1 ][ 0 ] - work[ i - 1 ][ 0 ] ) * delta1_inv2
                                    +   ( work[ i ][ 1 ] - work[ i ][ 0 ] ) * delta2_inv1 ;
        work_result[ i ][ Ny - 1 ]  =   ( work[ i + 1  ][ Ny - 1 ] - work[ i - 1 ][ Ny - 1 ] ) * delta1_inv2
                                    +   ( work[ i ][ Ny - 1 ] - work[ i ][ Ny - 2 ] ) * delta2_inv1 ;
     }
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



     //bulk of array~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     for ( int i = 1 ; i < Nx - 1 ; i++ ){
        for ( int j = 1 ; j < Ny - 1 ; j++ ){
           work_result[ i ][ j ]   =   ( work[ i + 1 ][ j ] - work[ i - 1 ][ j ] ) * delta1_inv2 
                                   +   ( work[ i ][ j + 1 ] - work[ i ][ j - 1 ] ) * delta2_inv2 ; //nabla times function
        }
     }
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

     //transforming result back to input format
     entry = 0 ;
     for ( int i = 0 ; i < Nx ; i++ ){
        for ( int j = 0 ; j < Ny ; j++ ){
           result[ entry ]  =  work_result[ i ][ j ];
           entry++;
        }
     }
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


     for ( int i = 0 ; i < Nx ; i++ ){
        delete [] work[ i ] ;
        delete [] work_result[ i ] ; 
     }

     delete [ ] work ;
     delete [ ] work_result ;
     work = 0 ;
 }


  //**********************************************************************************

  void derivative_1d( double *& func , double delta , int N , double *& result ){


     double delta_inv1 ;
     double delta_inv2 ;



     //defining inverse elements ~~~~~~~~~~~
     delta_inv2  =  1.0 / ( 2.0 * delta ) ;
     delta_inv1  =  1.0 / ( delta ) ;
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


     //defining edge derivatives ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     result[ 0 ]       =   ( func[ 1 ]  -  func[ 0 ] ) * delta_inv1 ;
     result[ N - 1 ]   =   ( func[ N - 1 ]  -  func[ N - 2 ] ) * delta_inv1 ;
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



     //Walking along min_x and max_x ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     for ( int i = 1 ; i < N - 1 ; i++ ){
         result[ i ]    =   (  func[ i + 1 ]  -  func[ i - 1 ] ) * delta_inv2 ;
     }
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}
