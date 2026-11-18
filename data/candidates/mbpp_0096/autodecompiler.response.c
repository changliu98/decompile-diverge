int func0(int n)
{
    int i;
    int counter = 0;

    for(i = 1; ; i++)
    {
        if(i > n)
            break;

        if(n % i == 0)
            counter++;
    }

    return counter;
}