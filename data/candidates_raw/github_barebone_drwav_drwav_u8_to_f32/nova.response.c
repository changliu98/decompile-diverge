static void func0(float *out, const uint8_t *in, const size_t len)
{
    size_t i;

    if (!out ||!in)
        return;

    for (i = 0; i < len; i++) {
        float v = (float)in[i];
        v = v * (1.0f / 128.0f) - 1.0f;
        out[i] = v;
    }
}