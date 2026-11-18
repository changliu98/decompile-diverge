int removeElement(int* nums, int numsSize, int val) {
    int i = 0;
    while(1){
        if(i >= numsSize)
            break;
        if(nums[i] == val){
            nums[i] = nums[--numsSize];
        }else{
            i++;
        }
    }
    return numsSize;
}