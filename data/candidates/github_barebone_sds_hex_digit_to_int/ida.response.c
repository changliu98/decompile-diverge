int __cdecl hex_digit_to_int(char c)
{
  int v2; // [rsp+Ch] [rbp-4h]

  switch ( c )
  {
    case '0':
      v2 = 0;
      break;
    case '1':
      v2 = 1;
      break;
    case '2':
      v2 = 2;
      break;
    case '3':
      v2 = 3;
      break;
    case '4':
      v2 = 4;
      break;
    case '5':
      v2 = 5;
      break;
    case '6':
      v2 = 6;
      break;
    case '7':
      v2 = 7;
      break;
    case '8':
      v2 = 8;
      break;
    case '9':
      v2 = 9;
      break;
    case 'A':
    case 'a':
      v2 = 10;
      break;
    case 'B':
    case 'b':
      v2 = 11;
      break;
    case 'C':
    case 'c':
      v2 = 12;
      break;
    case 'D':
    case 'd':
      v2 = 13;
      break;
    case 'E':
    case 'e':
      v2 = 14;
      break;
    case 'F':
    case 'f':
      v2 = 15;
      break;
    default:
      v2 = 0;
      break;
  }
  return v2;
}