const char *__cdecl func0(int year)
{
  const char *sign; // [rsp+10h] [rbp-10h]

  switch ( (year - 2000) % 12 + ((year - 2000) % 12 < 0 ? 0xC : 0) )
  {
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
    case 0xA:
      sign = "Tiger";
      break;
    default:
      sign = "Hare";
      break;
  }
  return sign;
}