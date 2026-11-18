void swap (int *x, int *y){

    if(x == NULL || y== NULL) return;

    int temp = *x;
    *x = *y;
    *y= temp;

    return ;
}