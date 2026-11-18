
void sun_mjulianday2date(
    long daynum,
    int *year,
    int *month,
    int *day
) {

 int f, e, g, h;


 daynum = daynum + 2400001;

 f = daynum + 1401 + (((4*daynum+274277)/146097)*3)/4 - 38;
 e = 4*f + 3;
 g = (e % 1461) / 4;
 h = 5*g+2;
 *day = (h % 153)/5 + 1;
 *month = (((h / 153)+2) % 12) + 1;
 *year = (e / 1461) - 4716 + ((14-*month)/12);

}
