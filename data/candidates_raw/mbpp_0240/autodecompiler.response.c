void concat(int arr1[], int size1, int arr2[], int size2, int arr[])
{
    int i,j;
    for(i=0;i<size1-1;i++)
    {
        arr[i]=arr1[i];
    }
    for(j=0;j<size2;j++)
    {
        arr[j+(size1-1)]=arr2[j];
    }
}