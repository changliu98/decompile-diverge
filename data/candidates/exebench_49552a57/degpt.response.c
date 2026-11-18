int matV4toV3(double *src_vec, double *dst_vec)
{
    // Copy the x component from the 4D vector to the 3D vector
    *dst_vec = *src_vec;
    // Copy the y component from the 4D vector to the 3D vector
    dst_vec[1] = src_vec[1];
    // Copy the z component from the 4D vector to the 3D vector
    dst_vec[2] = src_vec[2];
    // Return success status
    return 0;
}