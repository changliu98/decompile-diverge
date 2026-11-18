void combain_sorted_array(int *a, int *b, int *c)
{
    int *a1 = a; int *b1 = b; int *a2 = a + 5; int *b2 = b + 5;
    int *d;
    while (a < a2 && b < b2)
    {
        if (*a < *b)
        {
            if (a == a + 5 - 1)
            {
                *c = *a;
                d = c + 1;
                while (b < b2)
                {
                    *d = *b;
                    d++;
                    b++;
                }
                return;
            }
            else
            {
                *c = *a;
                a++;
                c++;
            }
        }
        else
        {
            if (b == b + 5 - 1)
            {
                *c = *b;
                c++;
                while (a < a2)
                {
                    *c = *a;
                    c++;
                    a++;
                }
                return;
            }
            else
            {
                *c = *b;
                b++;
                c++;
            }
        }
    }
}