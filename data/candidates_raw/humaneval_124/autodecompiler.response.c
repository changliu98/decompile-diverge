int valid_date(char * s)
{
  int i;
  char str_month[3], str_day[3], str_year[5];
  int month, day, year;
  int leap = 0;

  if (strlen(s) != 10)
  {
    return 0;
  }

  for (i = 0; i < 10; i++)
  {
    switch(i)
    {
      case 2:
      case 5:
        if (*(s + i) != '-')
          return 0;
        break;
      default:
        if (*(s + i) < '0' || *(s + i) > '9')
          return 0;
        break;
    }
  }

  *(str_month + 0) = *(s + 0);
  *(str_month + 1) = *(s + 1);
  *(str_month + 2) = '\0';

  *(str_day + 0) = *(s + 3);
  *(str_day + 1) = *(s + 4);
  *(str_day + 2) = '\0';

  *(str_year + 0) = *(s + 6);
  *(str_year + 1) = *(s + 7);
  *(str_year + 2) = *(s + 8);
  *(str_year + 3) = *(s + 9);
  *(str_year + 4) = '\0';

  month = atoi(str_month);
  day = atoi(str_day);
  year = atoi(str_year);

  if (month < 1 || month > 12)
    return 0;

  if (day < 1 || day > 31)
    return 0;

  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    return 0;

  if (month == 2)
  {
    if (year % 4 == 0)
      leap = 1;
    if (leap == 0 && day > 28)
      return 0;
    if (leap == 1 && day > 29)
      return 0;
  }

  return 1;
}