char *func0(int year)
{
  int offset = (year - 2000) % 12;
  char *sign = ((void *)0);
  if (offset < 0)
    offset += 12;
  switch (offset) {
  case 0:
    sign = "Dragon";
    break;
  case 1:
    sign = "Snake";
    break;
  case 2:
    sign = "Horse";
    break;
  case 3:
    sign = "sheep";
    break;
  case 4:
    sign = "Monkey";
    break;
  case 5:
    sign = "Rooster";
    break;
  case 6:
    sign = "Dog";
    break;
  case 7:
    sign = "Pig";
    break;
  case 8:
    sign = "Rat";
    break;
  case 9:
    sign = "Ox";
    break;
  case 10:
    sign = "Tiger";
    break;
  case 11:
    sign = "Hare";
    break;
  default:
    break;
  }
  return sign;
}