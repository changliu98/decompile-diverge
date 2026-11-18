int func0(int n, int m){
    char isNot = 1;
    while(isNot){
        if((n>0) && (m>0)){
            n /= 10;
            m /= 10;
        }else{
            isNot = 0;
        }
    }

    char result;
    if((n==0) && (m==0)){
        result = 1;
    }else{
        result = 0;
    }

    return result;
}