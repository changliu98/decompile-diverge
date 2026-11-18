int func0() {

    int n;
    scanf__bench("%d",&n);
    int arr[n];
    for(int i = 0;i < n;i++) {
        scanf__bench("%d",&arr[i]);
    }
    printf__bench("%d\n",mode(n,arr));
    return 0;
}