void func0(int *nums, int size)
{
    int i, j, gap, temp;
    int flag = 1;
    float shrink_fact = 1.3;

    for (gap = size; gap > 1; gap = (int)(gap / shrink_fact))
    {
        flag = 0;
        for (i = 0; i + gap < size; i++)
        {
            if (nums[i] > nums[i + gap])
            {
                temp = nums[i];
                nums[i] = nums[i + gap];
                nums[i + gap] = temp;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
}