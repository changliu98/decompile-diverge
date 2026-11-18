float __cdecl vectorDotProduct(int length, const float *vector1, const float *vector2)
{
    float dotProduct = 0.0f;

    for (int i = 0; i < length; ++i)
    {
        dotProduct += vector1[i] * vector2[i];
    }

    return dotProduct;
}