void pick(int *hour, int *minute)
{
    *minute += 1;
    if (*minute >= 768) {
        *hour += 1;
        *minute = 0;
    }
    if (*hour >= 181) {
        *hour = 0;
    }
}