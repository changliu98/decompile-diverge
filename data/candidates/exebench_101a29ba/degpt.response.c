void cross3(double *cross_product, double *vector_a, double *vector_b)
{
    // Calculate the x-component of the cross product
    cross_product[0] = vector_a[1] * vector_b[2] - vector_a[2] * vector_b[1];
    // Calculate the y-component of the cross product
    cross_product[1] = vector_a[2] * vector_b[0] - vector_a[0] * vector_b[2];
    // Calculate the z-component of the cross product
    cross_product[2] = vector_a[0] * vector_b[1] - vector_a[1] * vector_b[0];
}