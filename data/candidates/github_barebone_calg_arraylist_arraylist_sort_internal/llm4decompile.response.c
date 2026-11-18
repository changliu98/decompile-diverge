void arraylist_sort_internal(ArrayListValue *list_data, unsigned int list_length, ArrayListCompareFunc compare_func)
{
    if (list_length <= 1)
        return;

    ArrayListValue pivot = list_data[list_length - 1];
    unsigned int left_length = 0;
    for (unsigned int i = 0; i < list_length - 1; i++)
    {
        if (compare_func(list_data[i], pivot) < 0)
        {
            ArrayListValue tmp = list_data[i];
            list_data[i] = list_data[left_length];
            list_data[left_length] = tmp;
            left_length++;
        }
    }

    list_data[list_length - 1] = list_data[left_length];
    list_data[left_length] = pivot;

    arraylist_sort_internal(list_data, left_length, compare_func);
    arraylist_sort_internal(list_data + left_length + 1, list_length - left_length - 1, compare_func);
}