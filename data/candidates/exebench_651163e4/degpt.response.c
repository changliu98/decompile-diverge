int matV3toV4(double *src_vector, double *dst_vector)
{
    // Copy the first component of the 3D vector to the first component of the 4D vector
    *dst_vector = *src_vector;
    // Copy the second component of the 3D vector to the second component of the 4D vector
    dst_vector[1] = src_vector[1];
    // Copy the third component of the 3D vector to the third component of the 4D vector
    dst_vector[2] = src_vector[2];
    // Set the fourth component of the 4D vector to a constant value
    dst_vector[3] = DAT_00102008;
    // Return success status
    return 0;
}