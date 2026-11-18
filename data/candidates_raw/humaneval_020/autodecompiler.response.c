void get_closest_pair(float *a, int n, float *pair)
{
    float min_diff = FLT_MAX;
    pair[0] = a[0];
    pair[1] = a[1];

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            float diff = fabs(a[i] - a[j]);
            if(diff < min_diff)
            {
                min_diff = diff;
                pair[0] = a[i];
                pair[1] = a[j];
            }
        }
    }

    if(pair[0] > pair[1])
    {
        float temp = pair[0];
        pair[0] = pair[1];
        pair[1] = temp;
    }
}