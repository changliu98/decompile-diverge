int func0(int c[], int count)
{
    char flush = 0;
    if(count == 0)
        flush = 1;
    else
    {
        int i;
        for(i=1; i<count; i++)
        {
            if(c[i] < c[i-1])
            {
                flush = 0;
                break;
            }
            else if(i>1 && c[i] == c[i-1] && c[i] == c[i-2])
            {
                flush = 0;
                break;
            }
            else
                flush = 1;
        }
    }

    return ((flush & 1) ? 1 : 0);
}