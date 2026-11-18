void func0(int num, int *arr) {
    int even = 0, odd = 0;
    num = abs(num);
    do {
        if (num % 2 == 0)
            even++;
        else
            odd++;
        num /= 10;
    } while (num > 0);
    arr[0] = even;
    arr[1] = odd;
}