void geom_cross3d(double *vec_a, double *vec_b, double *cross_product)
{
    // Calculate the x-component of the cross product
    cross_product[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    // Calculate the y-component of the cross product
    cross_product[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    // Calculate the z-component of the cross product
    cross_product[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
}