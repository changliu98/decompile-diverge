int func0(int a)
{
    int i;
    int count;
    int result;

    if (a < 2) {
        result = 0;
    } else {
        count = 0;
        for (i = 2; (i * i) <= a; i++) {
            while ((a % i) == 0) {
                count++;
                a /= i;
            }
        }
        if (a > 1) {
            count++;
        }
        result = (count == 3);
    }

    return result;
}