void __cdecl dot(const float *v1, const float *v2, float *result)
{
    float sum = 0.0f;

    for (int i = 0; i < 4; ++i)
    {
        sum += v1[i] * v2[i];
    }

    *result = sum;
}