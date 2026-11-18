int get_unit(char *unit)
{
  if (unit[0] == 'p' && unit[1] == 'x')
    return 1;
  if (unit[0] == 'p' && unit[1] == 't')
    return 2;
  if (unit[0] == 'p' && unit[1] == 'c')
    return 3;
  if (unit[0] == 'm' && unit[1] == 'm')
    return 4;
  if (unit[0] == 'c' && unit[1] == 'm')
    return 5;
  if (unit[0] == 'i' && unit[1] == 'n')
    return 6;
  if (unit[0] == '%')
    return 7;
  if (unit[0] == 'e' && unit[1] == 'm')
    return 8;
  if (unit[0] == 'e' && unit[1] == 'x')
    return 9;
  return 0;
}