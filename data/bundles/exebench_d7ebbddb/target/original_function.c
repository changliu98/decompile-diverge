void raw_relu_bulk_apply_function( int n, float *ptr ) {
  int i;
  for( i = 0; i < n; i++ ) {
    ptr[i] = ( ptr[i] > 0.0 ? ptr[i] : 0.0 );
  }
}