void rsQuat_toMat(const float *q, float *m) {
    // Check if the first 3 components (x, y, z) of the quaternion are 0.0f
    if (q[0] == 0.0f && q[1] == 0.0f && q[2] == 0.0f) {
        // Identity Matrix
        m[0]  = 1.0f; m[1]  = 0.0f; m[2]  = 0.0f; m[3]  = 0.0f;
        m[4]  = 0.0f; m[5]  = 1.0f; m[6]  = 0.0f; m[7]  = 0.0f;
        m[8]  = 0.0f; m[9]  = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
        m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
    } else {
        // Compute the squared magnitude of the quaternion
        float norm_sq = q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3];
        
        // Calculate the scaling factor (2.0f / norm_sq)
        float s = 2.0f / norm_sq;
        
        // Precompute scaled components
        float xs = q[0] * s;
        float ys = q[1] * s;
        float zs = q[2] * s;
        float wx = q[3] * xs;
        float wy = q[3] * ys;
        float wz = q[3] * zs;
        float xx = q[0] * xs;
        float xy = q[0] * ys;
        float xz = q[0] * zs;
        float yy = q[1] * ys;
        float yz = q[1] * zs;
        float zz = q[2] * zs;
        
        // Compute the rotation matrix
        m[0]  = 1.0f - (yy + zz);
        m[1]  = xy + wz;
        m[2]  = xz - wy;
        m[3]  = 0.0f;
        
        m[4]  = xy - wz;
        m[5]  = 1.0f - (xx + zz);
        m[6]  = yz + wx;
        m[7]  = 0.0f;
        
        m[8]  = xz + wy;
        m[9]  = yz - wx;
        m[10] = 1.0f - (xx + yy);
        m[11] = 0.0f;
        
        m[12] = 0.0f;
        m[13] = 0.0f;
        m[14] = 0.0f;
        m[15] = 1.0f;
    }
}