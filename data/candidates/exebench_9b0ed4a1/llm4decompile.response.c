float binary_search(float value, float array[], int size)
{
    int low = 0;
    int high = size - 1;
    int mid;
    float alpha;


    if (value == array[0])
        return 0;


    if (value < array[0])
        return -1;


    if (value > array[size - 1])
        return size;


    if (value == array[size - 1])
        return size - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (value < array[mid])
            high = mid - 1;
        else if (value > array[mid])
            low = mid + 1;
        else
            return mid;
    }


    alpha = (value - array[high]) / (array[low] - array[high]);
    return (float) (high * (1 - alpha) + low * alpha);
}