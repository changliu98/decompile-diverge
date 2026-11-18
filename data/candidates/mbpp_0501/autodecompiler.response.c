int func0(int a, int b)
{
    int c = ngcd(a, b);
    int divs = 0;
    int top = sqrt((double) c);
    int i;

    for (i = 1; ; i++) {
        if (i > top) {
            return divs;
        } else if (c % i == 0) {
            divs += 2;
            int other = c / i;
            if (other == i) {
                divs--;
            }
        }
    }
}