float get_near_num(float target_num, float *near_num, float *near_num_before)
{
    float temp;

    if (near_num < near_num_before)
    {
        temp = *near_num_before;
        *near_num_before = *near_num;

        return temp;
    }

    return target_num;
}