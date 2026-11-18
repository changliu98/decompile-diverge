
void add_a_vector(double factor, int dim, double *init_vec, double *final_vec)
{
  do {
    *(final_vec++) += factor * (*(init_vec++));
  } while (--dim);

}
