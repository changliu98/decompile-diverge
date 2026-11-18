void normalize_quat(float *q) {
    float norm = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
    
    for (int i = 0; i < 4; i++) {
        q[i] /= norm;
    }
}