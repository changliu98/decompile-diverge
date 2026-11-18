int func0(int *array, int n)
{
    int i;
    int lcm = array[0];
    for(i=2; ; i++)
    {
        if(i<n)
        {
            lcm = find_lcm(lcm, array[i]);
        }
        else
        {
            break;
        }
    }
    return lcm;
}