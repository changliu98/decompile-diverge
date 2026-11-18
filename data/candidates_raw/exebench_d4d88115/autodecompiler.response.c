void caldat(int day, int month, int year, long *serial)
{
    long l;

    year += 100;
    if (month > 2) {
 month -= 3;
    } else {
 month += 9;
 --year;
    }
    year = year * 1461L;
    year /= 4;
    month = month * 153L;
    month += 2;
    month /= 5;
    l = year + month + day;
    l -= 36525L;
    if (l >= 60) --l;
    *serial = l;
}