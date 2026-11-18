void crossp(double *result, double *vector_a, double *vector_b)
{
    // Calculate the cross product of vectors u and v, storing the result in h
    // h[0] = u_y * v_z - u_z * v_y
    result[0] = vector_a[1] * vector_b[2] - vector_a[2] * vector_b[1];
    // h[1] = u_z * v_x - u_x * v_z
    result[1] = vector_a[2] * vector_b[0] - vector_a[0] * vector_b[2];
    // h[2] = u_x * v_y - u_y * v_x
    result[2] = vector_a[0] * vector_b[1] - vector_a[1] * vector_b[0];
}