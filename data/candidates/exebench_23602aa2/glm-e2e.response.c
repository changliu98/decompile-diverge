void lib3ds_quat_scalar(float *quat, float scalar) {
    for (int i = 0; i < 4; i++) {
        quat[i] *= scalar;
    }
}