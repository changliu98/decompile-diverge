int max(float* array)
{
    int i;
    int max_index = 0;
    float max_value = array[0];
    for(i = 0; i < 2; i++)
    {
        if(array[i] > max_value)
        {
            max_value = array[i];
            max_index = i;
        }
    }
    return max_index;
}