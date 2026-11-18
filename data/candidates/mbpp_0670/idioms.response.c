_Bool func0(int *array, int size){
    for(int i = 0; i < size - 1; i++){
        if(array[i] >= array[i+1])
            return 0;
    }
    return 1;
}