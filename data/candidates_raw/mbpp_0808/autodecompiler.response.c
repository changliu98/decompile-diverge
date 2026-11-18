int search(int tup[], int size, int val)
{
    char found = 0;
    int i = 0;

    while(1)
    {
        if (i >= size)
            break;

        if (tup[i] == val)
        {
            found = 1;
            break;
        }

        i++;
    }

    return (found && 1);
}