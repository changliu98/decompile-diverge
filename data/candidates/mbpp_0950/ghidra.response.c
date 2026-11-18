char * func0(int year)

{
  int remainder;
  char *sign;
  int year_local;
  
  remainder = (year + -2000) % 0xc;
  if (remainder < 0) {
    remainder = remainder + 0xc;
  }
  switch(remainder) {
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
  default:
    sign = "Hare";
  }
  return sign;
}