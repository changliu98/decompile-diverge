void geom_matmat3f(float *matA, float *matB, float *matC)
{
    *(matC) = (*(matA)) * (*(matB)) + (*(matA + 3)) * (*(matB + 1)) + (*(matA + 6)) * (*(matB + 2));
    *(matC + 1) = (*(matA + 1)) * (*(matB)) + (*(matA + 4)) * (*(matB + 1)) + (*(matA + 7)) * (*(matB + 2));
    *(matC + 2) = (*(matA + 2)) * (*(matB)) + (*(matA + 5)) * (*(matB + 1)) + (*(matA + 8)) * (*(matB + 2));

    *(matC + 3) = (*(matA)) * (*(matB + 3)) + (*(matA + 3)) * (*(matB + 4)) + (*(matA + 6)) * (*(matB + 5));
    *(matC + 4) = (*(matA + 1)) * (*(matB + 3)) + (*(matA + 4)) * (*(matB + 4)) + (*(matA + 7)) * (*(matB + 5));
    *(matC + 5) = (*(matA + 2)) * (*(matB + 3)) + (*(matA + 5)) * (*(matB + 4)) + (*(matA + 8)) * (*(matB + 5));

    *(matC + 6) = (*(matA)) * (*(matB + 6)) + (*(matA + 3)) * (*(matB + 7)) + (*(matA + 6)) * (*(matB + 8));
    *(matC + 7) = (*(matA + 1)) * (*(matB + 6)) + (*(matA + 4)) * (*(matB + 7)) + (*(matA + 7)) * (*(matB + 8));
    *(matC + 8) = (*(matA + 2)) * (*(matB + 6)) + (*(matA + 5)) * (*(matB + 7)) + (*(matA + 8)) * (*(matB + 8));
}