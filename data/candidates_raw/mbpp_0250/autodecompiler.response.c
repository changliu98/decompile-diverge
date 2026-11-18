int count_number_in_array(int *p,int array_size,int n)
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