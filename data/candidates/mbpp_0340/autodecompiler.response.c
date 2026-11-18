int func0(int* nums, int numsSize) {
    int temp[numsSize];
    int i=0;
    int j=0;
    int k=0;
    int sum=0;

    while(1){
        if(j>=numsSize)
            break;
        if(nums[j]>0){
            temp[k++] = nums[j];
        }
        j++;
    }

    qsort(temp,k,sizeof(int),compare);

    while(1){
        if(i>2)
            break;
        if(i<k)
            sum += temp[i];
        else
            break;
        i++;
    }

    return sum;
}