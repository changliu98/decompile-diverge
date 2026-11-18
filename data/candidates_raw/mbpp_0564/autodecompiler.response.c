int sockMerchant(int n, int* ar) {


    int count = 0;
    int i = 0;
    while(1){
        if(i >= n){
            break;
        }
        int j = i + 1;
        while(1){
            if(j >= n){
                break;
            }
            if(ar[i] == ar[j]){
                count++;
                j = n;
            }
            j++;
        }
        i++;
    }
    return count;

}