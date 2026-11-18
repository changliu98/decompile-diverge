void reverseInt(int *a)
{
    int i;
    for(i=0;i<5;i++)
    {
        int temp = a[i];
        a[i] = a[9-i];
        a[9-i] = temp;
    }
}