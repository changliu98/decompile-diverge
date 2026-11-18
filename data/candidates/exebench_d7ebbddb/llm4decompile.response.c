void raw_relu_bulk_apply_function(int n, float *ptr)
{
    int k;
    for (k = 0; k < n; ++k) {
        float v = ptr[k];
        ptr[k] = v > 0 ? v : 0;
    }
}