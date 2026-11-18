void sseround(float *values)
{
    // Round vec[0] to nearest 16-byte aligned boundary using SSE-style masking
    values[0] = (float)((uint)(float)(int)(float)((uint)*values & sseround::mask._0_4_) |
                     ~sseround::mask._0_4_ & (uint)*values);
    // Round vec[1] to nearest 16-byte aligned boundary using SSE-style masking
    values[1] = (float)((uint)(float)(int)(float)((uint)values[1] & sseround::mask._4_4_) |
                     ~sseround::mask._4_4_ & (uint)values[1]);
    // Round vec[2] to nearest 16-byte aligned boundary using SSE-style masking
    values[2] = (float)((uint)(float)(int)(float)((uint)values[2] & sseround::mask._8_4_) |
                     ~sseround::mask._8_4_ & (uint)values[2]);
    // Round vec[3] to nearest 16-byte aligned boundary using SSE-style masking
    values[3] = (float)((uint)(float)(int)(float)((uint)values[3] & sseround::mask._12_4_) |
                     ~sseround::mask._12_4_ & (uint)values[3]);
}