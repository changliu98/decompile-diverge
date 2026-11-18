int divisors_power_of_two(int n) {
    int power_of_two_divisors = 0;
    int i = 1;
    while (true) {
        if (i > n) {
            break;
        }
        int temp = i;
        while (true) {
            if (temp == 0) {
                break;
            }
            if (temp % 2 == 0) {
                power_of_two_divisors++;
            }
            temp /= 2;
        }
        i++;
    }
    return power_of_two_divisors;
}