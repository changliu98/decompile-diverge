int func0(int N)
{
    int last_two_numbers = N % 100;
    int res = (23 * last_two_numbers) / 100;
    int num_of_leap_years = N / 4;
    int num_of_century_years = N / 100;
    int num_of_400_years = N / 400;

    res += num_of_leap_years;
    if (num_of_century_years > 0) {
        res -= num_of_century_years;
    }
    if (num_of_400_years > 0) {
        res += num_of_400_years;
    }
    res %= 7;

    return res;
}