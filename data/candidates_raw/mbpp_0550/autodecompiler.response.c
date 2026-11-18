int func0(int *a, int l, int h) {
    int m, x;
    if (h < l)
        x = a[0];
    else if (h == l)
        x = a[l];
    else {
        m = l + (h-l)/2;
        if (m<h && a[m+1]<a[m])
            x = a[m];
        else if (m>l && a[m-1]>a[m])
            x = a[m-1];
        else if (a[l] > a[m])
            x = func0(a, l, m-1);
        else
            x = func0(a, m+1, h);
    }
    return x;
}