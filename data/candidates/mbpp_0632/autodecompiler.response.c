void func0(int* nums, int numsSize, int* numsMove) {
    int count=0;
    int j=0;
    for(int i=0;i<numsSize;i++)
    {
        if(nums[i]==0)
        {
            count++;
        }
        else
        {
            numsMove[j++]=nums[i];
        }
    }
    for(int i=0;i<count;i++)
    {
        numsMove[j++]=0;
    }
}