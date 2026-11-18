void __cdecl easterg(int year, int *month, int *day)
{
  int m; // [rsp+8h] [rbp-48h]
  int l; // [rsp+Ch] [rbp-44h]
  int h; // [rsp+18h] [rbp-38h]

  h = (year / 100 + 19 * (year % 19) - year / 100 / 4 - (year / 100 - (year / 100 + 8) / 25 + 1) / 3 + 15) % 30;
  l = (2 * (year % 100 / 4) + 2 * (year / 100 % 4) + 32 - h - year % 100 % 4) % 7;
  m = (22 * l + 11 * h + year % 19) / 451;
  *month = (l + h - 7 * m + 114) / 31;
  *day = (l + h - 7 * m + 114) % 31 + 1;
}