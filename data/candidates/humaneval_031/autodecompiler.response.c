int func0(long long int n){
    char flag;
    long long int i;
    if(n<3)
        flag=0;
    else{
        for(i=2;i*i<=n;i++){
            if(n%i==0){
                flag=0;
                break;
            }
            else
                flag=1;
        }
    }
    return (flag&1);
}