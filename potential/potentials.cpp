






void potential1( double *& pot , double *& r , int N , double charge ){

  //Function which return a completely spherical potential;
  //Coulomb potential where a charge can be passed
  
  for ( int i = 0 ; i < N ; i++ ){
     pot[ i ]  =   coulomb * charge / r [ i ] ;
  }

  }
