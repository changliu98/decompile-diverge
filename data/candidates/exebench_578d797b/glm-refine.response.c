void __cdecl add_a_vector(double factor, int dim, double *init_vec, double *final_vec)
{
    for (int i = 0; i < dim; ++i)
    {
        final_vec[i] = factor * init_vec[i] + final_vec[i];
    }
}