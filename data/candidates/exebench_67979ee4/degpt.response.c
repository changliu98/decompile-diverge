void quaternionComposition(float q0_w, float q0_x, float q0_y, float q0_z, float q1_w, float q1_x, float q1_y, float q1_z, float *q2_w, float *q2_x, float *q2_y, float *q2_z)
{
    // Calculate the scalar component of the resulting quaternion (w)
    *q2_w = -q0_z * q1_z - q0_y * q1_y + q0_w * q1_w - q0_x * q1_x;
    
    // Calculate the first vector component of the resulting quaternion (x)
    *q2_x = -q0_z * q1_y + q0_y * q1_z + q0_w * q1_x + q0_x * q1_w;
    
    // Calculate the second vector component of the resulting quaternion (y)
    *q2_y = q0_z * q1_x + q0_y * q1_w + q0_w * q1_y - q0_x * q1_z;
    
    // Calculate the third vector component of the resulting quaternion (z)
    *q2_z = q0_z * q1_w - q0_y * q1_x + q0_w * q1_z + q0_x * q1_y;
}