int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf__bench("%.5f\n", geom_mean(arr, n));

    int arr2[] = { 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf__bench("%.5f\n", geom_mean(arr2, n2));

    int arr3[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf__bench("%.5f\n", geom_mean(arr3, n3));

    int arr4[] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf__bench("%.5f\n", geom_mean(arr4, n4));

    return 0;
}