int char2int(char c)
{
  int i = 0;
  switch (c)
  {
    case '0':
      i = 0;
      break;
    case '1':
      i = 1;
      break;
    case '2':
      i = 2;
      break;
    case '3':
      i = 3;
      break;
    case '4':
      i = 4;
      break;
    case '5':
      i = 5;
      break;
    case '6':
      i = 6;
      break;
    case '7':
      i = 7;
      break;
    case '8':
      i = 8;
      break;
    case '9':
      i = 9;
      break;
    case 'a':
    case 'A':
      i = 10;
      break;
    case 'b':
    case 'B':
      i = 11;
      break;
    case 'c':
    case 'C':
      i = 12;
      break;
    case 'd':
    case 'D':
      i = 13;
      break;
    case 'e':
    case 'E':
      i = 14;
      break;
    case 'f':
    case 'F':
      i = 15;
      break;
    default:
      i = 0;
      break;
  }
  return i;
}