int __cdecl func0(int n)
{
    int mask = 0;
    int pos = 0;

    for (int temp = n; temp > 0; temp >>= 1, pos++) {
        if (pos & 1)
            mask |= 1 << pos;
    }

    return n ^ mask;
}