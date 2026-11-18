char *func0(int *seq_nums, int n)
{
    int *diff = (int *)((int *)seq_nums + n);
    int i = 0;
    int j = 0;
    for(i = 1; i < n; i++)
    {
        diff[i - 1] = seq_nums[i] - seq_nums[i - 1];
    }
    for(i = 1; i < n - 1; i++)
    {
        if(diff[i] != diff[0])
        {
            char *str = "Non Linear Sequence";
            int flag = 1;
            return str;
        }
    }
    char *str = "Linear Sequence";
    int flag = 1;
    return str;
}