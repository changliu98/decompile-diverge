void mat3f_from_mat3d(struct mat3f *dest, const struct mat3d *src)
{
    int i;
    for (i = 0; i < 9; i++) {
        ((float *) dest)[i] = ((double *) src)[i];
    }
}