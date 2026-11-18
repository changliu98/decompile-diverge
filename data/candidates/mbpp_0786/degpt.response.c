int func0(int *arr, int size, int target)
{
    int index;
    for (index = 0; (index < size && (arr[index] <= target)); index = index + 1) {
    }
    return index;
}