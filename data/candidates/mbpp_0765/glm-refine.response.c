int __cdecl func0(int n)
{
    double log_val = log2((double)(n + 1));
    return n + 1 + (int)log2((double)(n + 1) + log_val);
}