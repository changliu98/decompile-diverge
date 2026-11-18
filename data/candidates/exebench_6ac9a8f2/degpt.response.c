void geom_cross3f(float *vec_a, float *vec_b, float *cross_product)
{
    // Compute the cross product of two 3D vectors a and b
    // result[0] = a_y * b_z - a_z * b_y
    cross_product[0] = vec_a[1] * vec_b[2] - vec_a[2] * vec_b[1];
    // result[1] = a_z * b_x - a_x * b_z
    cross_product[1] = vec_a[2] * vec_b[0] - vec_a[0] * vec_b[2];
    // result[2] = a_x * b_y - a_y * b_x
    cross_product[2] = vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0];
}