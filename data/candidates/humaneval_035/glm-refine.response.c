#include <float.h>

float find_max(const float *array, int size)
{
    float max_val = -FLT_MAX;
    
    for (int i = 0; i < size; ++i)
    {
        if (array[i] > max_val)
        {
            max_val = array[i];
        }
    }
    
    return max_val;
}