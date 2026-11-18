int func0(int* prices, int pricesSize) {
    int left[pricesSize];
    int i;
    for(i=0;i<pricesSize;i++){
        left[i] = prices[i];
    }
    int j;
    for(i=1;i<pricesSize;i++){
        for(j=0;j<i;j++){
            if(prices[i]>prices[j]){
                if(left[i]<left[j]+prices[i]){
                    left[i] = left[j]+prices[i];
                }
            }
        }
    }

    int right[pricesSize];
    for(i=0;i<pricesSize;i++){
        right[i] = prices[i];
    }
    for(i=1;i<pricesSize;i++){
        for(j=0;j<i;j++){
            if(prices[pricesSize-i-1]<prices[pricesSize-j-1]){
                if(right[pricesSize-i-1]<right[pricesSize-j-1]+prices[pricesSize-i-1]){
                    right[pricesSize-i-1] = right[pricesSize-j-1]+prices[pricesSize-i-1];
                }
            }
        }
    }

    int max = -9999999;
    for(i=0;i<pricesSize;i++){
        if(max<left[i]+right[i]-prices[i]){
            max = left[i]+right[i]-prices[i];
        }
    }
    return max;
}