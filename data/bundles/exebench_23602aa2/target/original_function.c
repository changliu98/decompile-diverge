void
lib3ds_quat_scalar(float c[4], float k) {
    int i;
    for (i = 0; i < 4; ++i) {
        c[i] *= k;
    }
}