int itochar(int num,char *strb){
    char stra[256];
    int i=0;
    int j=0;
    int k=0;
    while(num!=0){
        stra[i]=(num%10)+'0';
        i++;
        num=num/10;
    }
    while(j<i){
        strb[k]=stra[i-j-1];
        j++;
        k++;
    }
    return k;
}