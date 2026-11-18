void measure(long *inches, int *inch, int *feet, int *yard, int *mile)
{
    *inches = 63520;
    *inch = *inches;
    *feet = *inches / 12.0;
    *yard = *inches / 12.0 / 3.0;
    *mile = *inches / 12.0 / 3.0 / 1760.0;
}