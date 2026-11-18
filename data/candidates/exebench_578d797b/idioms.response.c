void add_a_vector(double factor, int dim, double *init_vec, double *final_vec)
{
  do { *final_vec++ += *init_vec++ * factor; } while (--dim);
}