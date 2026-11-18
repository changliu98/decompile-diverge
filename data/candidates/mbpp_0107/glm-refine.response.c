f digits in the hex representation
int __cdecl func0(int L, int R)
{
    int count = 0;

    for (int n = L; n <= R; ++n)
    {
        if (n < 10)
        {
            // single decimal digit, no hex letters
        }
        else if (n <= 15)
        {
            // single hex digit in {a,b,c,d,e,f}
            ++count;
        }
        else
        {
            // multi-digit hex: count digits whose value is >= 10 (i.e. a..f)
            for (int k = n; k; k /= 16)
            {
                if (k % 16 >= 10)
                    ++count;
            }
        }
    }

    return count;
}