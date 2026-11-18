void prod_vet(float *vec_a, float *vec_b, float *vec_c)
{
    // Calculate the z-component of the cross product of vectors x and y
    vec_a[2] = *vec_b * vec_c[1] - *vec_c * vec_b[1];
    // Calculate the z-component of the cross product of vectors y and z
    vec_b[2] = *vec_c * vec_a[1] - *vec_a * vec_c[1];
    // Calculate the z-component of the cross product of vectors z and x
    vec_c[2] = *vec_a * vec_b[1] - *vec_b * vec_a[1];
}