void __cdecl matvec4(double *A, double *B, double *C, double alpha, double beta)
{
    // Iterate over the 4 rows of matrix A
    for (int i = 0; i < 4; ++i)
    {
        double *row = &A[i * 4];
        
        // Compute the dot product of the current row of A and the vector B
        double dot_product = (row[0] * B[0]) + 
                             (row[1] * B[1]) + 
                             (row[2] * B[2]) + 
                             (row[3] * B[3]);
                             
        // Scale the accumulated dot product by alpha, add the scaled original 
        // value of C, and store the result back into C
        C[i] = (alpha * dot_product) + (beta * C[i]);
    }
}