void __cdecl add_a_vector(double factor, int dim, double *init_vec, double *final_vec)
{
  double *v4; // rax
  double v5; // xmm2_8
  double *v6; // rax

  do
  {
    v4 = init_vec++;
    v5 = *v4;
    v6 = final_vec++;
    *v6 = factor * v5 + *v6;
    --dim;
  }
  while ( dim );
}