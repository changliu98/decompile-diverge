void lib3ds_vector_max(float *result, float *input)
{
    for (int i = 0; i < 3; i++) {
        if (result[i] < input[i]) {
            result[i] = input[i];
        }
    }
}