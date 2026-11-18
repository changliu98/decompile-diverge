int func0(int *lst, int size)
{
    int positive_numbers[size];
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (lst[i] > 0)
        {
            positive_numbers[index] = lst[i];
            index++;
        }
    }

    qsort(positive_numbers, index, sizeof(int), compare);

    int sum = 0;
    for (int i = 0; i < 3 && i < index; i++)
    {
        sum += positive_numbers[i];
    }

    return sum;
}