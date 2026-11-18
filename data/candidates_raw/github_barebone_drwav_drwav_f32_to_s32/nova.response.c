static void func0(void *out, const void *in, size_t len)
{
    size_t i;
    float *out_ = out;
    const float *in_ = in;

    if (!out_ ||!in_)
        return;

    for (i = 0; i < len; i++)
        *out_++ = in_[i] * 32768.0f;
}