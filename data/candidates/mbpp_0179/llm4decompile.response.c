int func0(int x)
{
    int terms[100];
    int n = 0;
    int temp = x;
    while (temp > 0) {
        terms[n] = temp % 10;
        temp /= 10;
        n++;
    }

    int left = 0;
    int right = n - 1;
    while (left < right) {
        int temp = terms[left];
        terms[left] = terms[right];
        terms[right] = temp;
        left++;
        right--;
    }

    int next_term = 0;
    int i = n;
    while (next_term < x) {
        next_term = 0;
        int j;
        for (j = 1; j <= n; j++) {
            next_term += terms[i - j];
        }
        terms[i] = next_term;
        i++;
    }

    return next_term == x;
}