int minSubsequenceSum(int *src, int len){
    int i;
    int tmp, min;
    tmp = src[0];
    min = src[0];

    for(i=1; ;){
        if(i >= len){
            break;
        }

        if(tmp < 0){
            tmp = tmp + src[i];
        }else{
            tmp = src[i];
        }

        if(tmp < min){
            min = tmp;
        }

        i++;
    }
    return min;
}