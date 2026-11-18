void func(int *x, int *y)
{
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragma omp barrier
#pragmaomp parallel
    {
        *x = 1;
        *y = 1;
    }
}