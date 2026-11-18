int* getHint(char** guess, int guessRowSize, int guessColSize, int* returnSize) {
    int x,y;
    int i,j;
    int min;
    int *ret;

    for(i=0;i<guessRowSize;i++){
        for(j=0;j<guessRowSize;j++){
            if(guess[i][j]==1){
                x=i;
                y=j;
            }
        }
    }

    min = guessRowSize*guessRowSize;
    if(x-1>0 && guess[x-1][y]<min)
        min=guess[x-1][y];
    if(x+1<guessRowSize && guess[x+1][y]<min)
        min=guess[x+1][y];
    if(y-1>0 && guess[x][y-1]<min)
        min=guess[x][y-1];
    if(y+1<guessRowSize && guess[x][y+1]<min)
        min=guess[x][y+1];

    *returnSize = guessColSize;
    ret = (int*)malloc(sizeof(int)*guessColSize);
    for(i=0;i<guessColSize;i++){
        if(i%2==0)
            ret[i]=1;
        else
            ret[i]=min;
    }

    return ret;
}