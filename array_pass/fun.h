void func( double *& x , int N ){

 for ( int i = 0 ; i < N ; i++ ){
   x[ i ] = x[ i ] + x[ i ] ;
 }
}
