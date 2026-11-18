int next_arr_seq(int *list, int l_size, int max_val)
{
    int i = 0;
    int ret;
    while(1)
    {
        if(i >= l_size)
        {
            ret = 0;
            break;
        }
        list[i]++;
        if(list[i] <= max_val)
        {
            ret = 1;
            break;
        }
        else
        {
            list[i] = 0;
            i++;
        }
    }
    return ret;
}