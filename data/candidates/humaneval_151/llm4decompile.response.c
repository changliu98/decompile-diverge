long long func0(float lst[], int lst_size)
{
    int i;
    long long sum = 0;
    for (i = 0; i < lst_size; i++)
        if (fabsf(lst[i] - round(lst[i])) < 1e-5 && lst[i] > 0 && (int)round(lst[i]) % 2 == 1)
            sum += (int)round(lst[i]) * (int)round(lst[i]);
    return sum;
}