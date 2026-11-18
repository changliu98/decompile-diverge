void add_a_vector(double factor,int dim,double *init_vec,double *final_vec)

{
  double *final_vec_local;
  double *init_vec_local;
  int dim_local;
  double factor_local;
  
  final_vec_local = final_vec;
  init_vec_local = init_vec;
  dim_local = dim;
  do {
    *final_vec_local = factor * *init_vec_local + *final_vec_local;
    dim_local = dim_local + -1;
    final_vec_local = final_vec_local + 1;
    init_vec_local = init_vec_local + 1;
  } while (dim_local != 0);
  return;
}