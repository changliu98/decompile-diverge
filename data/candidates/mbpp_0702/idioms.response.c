int func0(int *array, int n, int k){
    int min = n-1;
    qsort(array, n, sizeof(int), strcmp);
    for(int i = 0; i < n; i++){
        int ind = find_ind(array[i], i, n, k, array);
        if(ind != -1){
            int temp = n - (ind - i + 1);
            int temp2 = n - (ind - i + 1);
            if(min < temp){
                temp = min;
            }
            min = temp;
        }
    }
    return min;
}