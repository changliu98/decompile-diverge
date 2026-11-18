void cross(double *vector_a, double *vector_b, double *result_vector)
{
    // Calculate the y-component of the cross product: va[2]*vb[3] - va[3]*vb[2]
    result_vector[1] = vector_a[2] * vector_b[3] - vector_a[3] * vector_b[2];
    // Calculate the z-component of the cross product: va[3]*vb[1] - va[1]*vb[3]
    result_vector[2] = vector_a[3] * vector_b[1] - vector_a[1] * vector_b[3];
    // Calculate the x-component of the cross product: va[1]*vb[2] - va[2]*vb[1]
    result_vector[3] = vector_a[1] * vector_b[2] - vector_a[2] * vector_b[1];
}