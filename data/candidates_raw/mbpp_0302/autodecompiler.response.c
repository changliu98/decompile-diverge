int reverseBits(int n) {
    int result;
    if(n == 0)
        result = 0;
    else{
        int i = 0;
        n = n/2;
        while(1){
            if(n>0){
                n = n/2;
                i++;
            }
            else
                break;
        }
        result = 1<<i;
    }
    return result;
}