void even(int start, int finish, int evens[], int *how_many)
{
    int temp;
    int i;

    *how_many = 0;

    if(finish < start)
    {
        temp = start;
        start = finish;
        finish = temp;
    }

    for(i = start ; i <= finish ; ++i)
    {
        if(i < 10 && i % 2 == 0)
        {
            evens[(*how_many)++] = i;
        }
    }
}