int func0(int *list, int size){
    int i, j, temp, num, sum, largest;
    bool isPrime;

    largest = 0;
    sum = 0;
    for(i=0; i<size; i++){
        num = list[i];
        if(num > 1){
            isPrime = true;
            for(j=2; j*j<=num; j++){
                if(num%j == 0){
                    isPrime = false;
                    break;
                }
            }

            if(isPrime){
                temp = (num > largest) ? num : largest;
                largest = temp;
            }
        }
    }

    while(largest > 0){
        sum += largest % 10;
        largest /= 10;
    }

    return sum;
}