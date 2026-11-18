void lib3ds_quat_copy(float *destination, float *source)
{
    for (int i = 0; i < 4; i++) {
        destination[i] = source[i];
    }
}