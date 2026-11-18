static void drwav_f64_to_f32(void *out, const void *in, size_t count)
{
    size_t i;

    if (!out &&!in)
        return;

    for (i = 0; i < count; i++)
        ((float *)out)[i] = ((const double *)in)[i];
}