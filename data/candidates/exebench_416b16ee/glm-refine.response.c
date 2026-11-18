// Sets the search space boundaries for the Rastrigin function optimization problem.
// If the dimension index is valid (greater than 0), it assigns the standard bounds.
void __cdecl set_rastrigin_bounds(double *lower_bound, double *upper_bound, int dimension_index)
{
    if (dimension_index > 0)
    {
        *lower_bound = -5.12;
        *upper_bound = 5.12;
    }
}