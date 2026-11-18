int func0(int *operations, int size)
{
    int i;
    int fuel = 0;

    for (i = 0; i < size; i++)
    {
        fuel += operations[i];

        if (fuel < 0)
        {
            return 1;
        }
    }

    return 0;
}