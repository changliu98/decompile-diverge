static void func0(float *output, short *compressed,
                                  unsigned int size) {
    unsigned int i;

    if (output == NULL || compressed == NULL)
        return;

    for (i = 0; i < size; i++)
        output[i] = (float)compressed[i] / 32768.0f;
}