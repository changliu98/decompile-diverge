void add_and_sub(int *x, int *y)
{
#pragma omp atomic update
    (*x)++;
#pragma omp atomic update
    (*y)--;
}