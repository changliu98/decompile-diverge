void __cdecl easterj(int year, int *month, int *day)
{
  int e; // [rsp+8h] [rbp-2Ch]

  e = (4 * (year % 7) + 2 * (year % 4) - (19 * (year % 19) + 15) % 30 + 34) % 7;
  *month = (e + (19 * (year % 19) + 15) % 30 + 114) / 31;
  *day = (e + (19 * (year % 19) + 15) % 30 + 114) % 31 + 1;
}