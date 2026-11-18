void combain_sorted_array(int *a, int *b, int *c)
{
    int *a_end = a + 5;
    int *b_end = b + 5;

    while (a < a_end && b < b_end) {
        if (*a > *b) {
            if (b == b_end - 1) {
                *c++ = *b;
                while (a < a_end) {
                    *c++ = *a++;
                }
            }
            *c++ = *b++;
        } else {
            if (a == a_end - 1) {
                *c++ = *a;
                while (b < b_end) {
                    *c++ = *b++;
                }
            }
            *c++ = *a++;
        }
    }
}