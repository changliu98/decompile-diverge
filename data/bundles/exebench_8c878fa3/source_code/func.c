#include <stdlib.h>

void sun_mjulianday_to_date(
    unsigned int mjd,
    int* year,
    int* month,
    int* day
) {
 int a, b, c;
 int d, e, m;

 a = (mjd + 2400001) + 32044;
 b = ((4*a) + 3) / 146097;
 c = a - ((b*146097) / 4);

 d = ((4*c)+3) / 1461;
 e = c - (1461*d) / 4;
 m = ((5*e) + 2) / 153;

 *day = e - ((153*m+2)/5) + 1;
 *month = m + 3 - (12 * (m / 10));
 *year = (b * 100) + d - 4800 + (m/10);
}
