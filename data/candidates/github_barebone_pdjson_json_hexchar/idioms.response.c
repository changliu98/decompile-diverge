int hexchar(int c)
{
  int ret;
  switch (c) {
  case '0':
    ret = 0;
    break;
  case '1':
    ret = 1;
    break;
  case '2':
    ret = 2;
    break;
  case '3':
    ret = 3;
    break;
  case '4':
    ret = 4;
    break;
  case '5':
    ret = 5;
    break;
  case '6':
    ret = 6;
    break;
  case '7':
    ret = 7;
    break;
  case '8':
    ret = 8;
    break;
  case '9':
    ret = 9;
    break;
  case 'a':
  case 'A':
    ret = 10;
    break;
  case 'b':
  case 'B':
    ret = 11;
    break;
  case 'c':
  case 'C':
    ret = 12;
    break;
  case 'd':
  case 'D':
    ret = 13;
    break;
  case 'e':
  case 'E':
    ret = 14;
    break;
  case 'f':
  case 'F':
    ret = 15;
    break;
  default:
    ret = -1;
    break;
  }
  return ret;
}