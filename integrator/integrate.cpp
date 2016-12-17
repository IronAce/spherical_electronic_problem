  double integrate2d( double *& func , int Nx , int Ny, double dx , double dy ){

  // trapezoidal method for calculating 2d integrals
  // should be compiled with -O1 option when using g++ 
  // compiler
  // Jonathan Lahnsteiner 18.11.2016

  
    double t1 ;
    double t2 ;
    double t3 ;
    double area ;
    double ** work_array ;
    int    row ;

    t1     =   0.0 ;
    t2     =   0.0 ;
    t3     =   0.0 ;
    area   =  dx * dy ;

    work_array  =  new double * [ Nx ] ;
    for ( int i = 0 ; i < Nx ; i++ ){
       work_array[ i ]  =  new double [ Ny ] ;
    }

    row = 0 ;
    for ( int i = 0 ; i < Nx ; i++ ){
       for ( int j = 0 ; j < Ny ; j++ ){
       work_array[ i ][ j ]  =  func[ row ] ;
       row++ ;
       }
    }

    //Walking along x; with y min or max
    for ( int i = 1 ; i < Nx - 1 ; i++ ){
      t1  +=  work_array[ i ][ 0 ] ;
      t1  +=  work_array[ i ][ Ny - 1 ] ;
    }

 
    //Walking along y; with x min or max
    for ( int i = 1 ; i < Ny - 1 ; i++ ){
      t1  +=  work_array[ 0 ][ i ] ;
      t1  +=  work_array[ Nx - 1 ][ i ] ;
    }
 
    t1  =  t1  * 0.5 ;

    //Counting edges
    t2  +=  work_array[ 0 ][ 0 ] ;
    t2  +=  work_array[ Nx - 1 ][ 0 ] ;
    t2  +=  work_array[ Nx - 1 ][ Ny - 1 ] ;
    t2  +=  work_array[ 0 ][ Ny - 1 ] ;
    t2  =   t2  *  0.25 ; 

    //Counting inbetween
    for ( int i = 1 ; i < Nx - 1 ; i++ ){
      for ( int j = 1 ; j < Ny - 1 ; j++ ){
         t3  +=  work_array[ i ][ j ] ; 
      }
    }

   for ( int i = 0 ; i < Nx ; i++ ){
       delete [ ] work_array[ i ] ;
   }
   delete [ ] work_array ;
   work_array   =  0 ;

   t1   +=  t2 ;
   t1   +=  t3 ;

   t1    =  t1   *  area;   

   return area;
  }


  double integrate1d( double *& func , int Nx , double dx ){

  // trapezoidal method for calculating 2d integrals
  // should be compiled with -O1 option when using g++ 
  // compiler
  // Jonathan Lahnsteiner 18.11.2016

  
    double t1 ;
    double t2 ;

    t2     =   0.0 ;

 
    //Walking along y; with x min or max
    t1   =  func[ 0 ] ;
    t1  +=  func[ Nx - 1 ] ; 
    t1  *=  0.5 ;

    //Counting bulk
    for ( int i = 1 ; i < Nx - 1 ; i++ ){
       t2  += func[ i ] ; 
    }

    t1   +=  t2 ;
    t1    =  t1   *  dx ;

   return area;
  }
