char** oddElements(char** arr, int n) {
    char** oddArr = (char**)malloc(n*sizeof(char*));
    int i, j, k, num;
    for(i=0;i<n;i++) {
        num = 0;
        for(j=0;arr[i][j] != '\0';j++) {
            if(arr[i][j] >= '0' && arr[i][j] <= '9') {
                if((arr[i][j]-'0')%2 == 1) {
                    num++;
                }
            }
        }
        oddArr[i] = (char*)malloc(100*sizeof(char));
        sprintf(oddArr[i],"the number of odd elements %d in the string %d of the %d input.",num,num,num);
    }
    return oddArr;
}