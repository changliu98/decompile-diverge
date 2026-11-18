int func0(int *array, int n, int x){
    int left = 0;
    int right = n - 1;
    int result = -1;
    while (left <= right){
        int mid = (right - left)/2 + left;
        if (array[mid] == x){
            result = mid;
            right = mid - 1;
        }
        else if (array[mid] > x){
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    }
    return result;
}