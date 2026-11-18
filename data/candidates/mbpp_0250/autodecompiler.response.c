int func0(int *p,int array_size,int n)
{
    int i,count=0;
    for (i=0; i<array_size; i++)
    {
        if (p[i]==n)
        {
            count++;
        }
    }
    return count;
}