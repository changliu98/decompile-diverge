void add_a_vector(int dim, double *init_vec, double *final_vec, double factor)
{
  int i;
  for(i=0; i<dim; i++)
    final_vec[i] += init_vec[i]*factor;
}