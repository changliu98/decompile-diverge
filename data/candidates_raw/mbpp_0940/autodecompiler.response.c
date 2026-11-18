void heap_sort(int *a, int n)
{
    heapify(a, n);
    int end = n - 1;
    while (end > 0) {
        do { int t = a[end]; a[end] = a[0]; a[0] = t; } while(0);;
        end--;
        shift_down(a, 0, end);
    }
}