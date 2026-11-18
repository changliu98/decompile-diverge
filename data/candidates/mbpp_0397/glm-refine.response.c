int __cdecl median_of_three(int a, int b, int c)
{
    if (a <= b) {
        if (a > c) {
            return a;
        } else if (b <= c) {
            return b;
        } else {
            return c;
        }
    } else {
        if (a <= c) {
            return a;
        } else if (b >= c) {
            return b;
        } else {
            return c;
        }
    }
}