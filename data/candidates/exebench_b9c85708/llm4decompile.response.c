void easterj(int year, int *month, int *day)
{
 int a, b, c, d, e, f, g;

 a = year % 19;
 b = year / 100;
 c = year % 100;
 d = (19 * a + b - b / 4 - ((8 * b + 13) / 25) + 15) % 30;
 e = (32 + 2 * (b % 4) + 2 * (c / 4) - d - (c % 4)) % 7;
 f = d + e - 7 * ((a + 11 * d + 22 * e) / 451) + 114;

 *month = f / 31;
 *day = f % 31 + 1;
}