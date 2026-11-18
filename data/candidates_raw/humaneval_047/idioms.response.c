float median(float *data, int size){
    int i; int j;
    float temp;
    for(i = 0; i < size; i++){
        for(j = i + 1; j < size; j++){
            if(data[i] > data[j]){
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    if(size % 2 == 1){
        return data[(size / 2)];
    }
    return (data[(size / 2)] + data[(size / 2) - 1]) / 2;
}