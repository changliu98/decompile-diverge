bool func0(const float *numbers, int size, float threshold)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            float diff = fabsf(numbers[i] - numbers[j]);
            if (diff < threshold)
                return true;
        }
    }
    return false;
}