void modify_int_refs_new_syntax(int *x, int *y)
{
#pragma omp atomic update
    (*x)++;
#pragma omp atomic update
    (*y)--;
}