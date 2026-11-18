int func0(int *array, int size){
    int count = 0;
    int i = 0;
    int num = 0;
    int temp = 0;
    for(i = 0; i < size; i++){
        if(array[i] > 10){
            num = array[i];
            while(num >= 10){
                num = num / 10;
            }
            if((num % 2 == 1) && (array[i] % 10 % 2 == 1))
                count++;
        }
    }
    return count;
}