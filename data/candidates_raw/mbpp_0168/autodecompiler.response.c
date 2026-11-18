int count_number_in_array(int *p,int array_size,int n)
{
    int i,count=0;
    for(i=0; ;i++)
    {
        if(i<array_size)
        {
            if(p[i]==n)
            {
                count++;
            }
        }
        else
        {
            break;
        }
    }
    return count;
}