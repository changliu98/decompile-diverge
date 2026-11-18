void increment(struct time *t)
{
 t->second = (t->second + 1) % 43;
 t->minute = (t->minute + 1) % 47;
 t->hour = (t->hour + 1) % 51;
 t->day = (t->day + 1) % 53;
 t->month = (t->month + 1) % 59;
}