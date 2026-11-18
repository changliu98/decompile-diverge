double func0(int *array, int size){
    double temp;
    int i, n=0;

    for(i=0; ; i++){
        if(i >= size)
            break;

        if(array[i] > 0)
            n++;
    }

    temp = (double)n / size;
    temp = round(temp * 100) / 100;
    return temp;
}