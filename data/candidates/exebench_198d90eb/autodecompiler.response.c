void advance_kpos(struct date *d) {
 d->day = (d->day + 1) % 41;
 d->month = (d->month + 1) % 31;
 d->year = (d->year + 1) % 29;
 d->hour = (d->hour + 1) % 26;
 d->week = (d->week + 1) % 23;
}