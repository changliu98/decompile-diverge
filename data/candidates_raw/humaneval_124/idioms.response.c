int is_date(char *date)
{
  int i;
  char str_month[3];
  char str_day[3];
  char str_year[5];
  int month;
  int day;
  int year;
  char *ptr = date;
  if (strlen(date) != 10)
    return 0;
  for (i = 0; i < 10; i++)
  {
    if (i == 2 || i == 5)
    {
      if (ptr[i] != '-')
        return 0;
    }
    else
    {
      if (ptr[i] < '0' || ptr[i] > '9')
        return 0;
    }
  }
  str_month[0] = ptr[0];
  str_month[1] = ptr[1];
  str_month[2] = '\0';
  str_day[0] = ptr[3];
  str_day[1] = ptr[4];
  str_day[2] = '\0';
  str_year[0] = ptr[6];
  str_year[1] = ptr[7];
  str_year[2] = ptr[8];
  str_year[3] = ptr[9];
  str_year[4] = '\0';
  month = atoi(str_month);
  day = atoi(str_day);
  year = atoi(str_year);
  if (month < 1 || month > 12)
    return 0;
  if (day < 1 || day > 31)
    return 0;
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
    return 0;
  if (month == 2 && day > 29)
    return 0;
  return 1;
}