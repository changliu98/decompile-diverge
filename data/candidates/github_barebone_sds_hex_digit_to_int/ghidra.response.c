int hex_digit_to_int(char c)

{
  char c_local;
  int local_c;
  
  switch(c) {
  case '0':
    local_c = 0;
    break;
  case '1':
    local_c = 1;
    break;
  case '2':
    local_c = 2;
    break;
  case '3':
    local_c = 3;
    break;
  case '4':
    local_c = 4;
    break;
  case '5':
    local_c = 5;
    break;
  case '6':
    local_c = 6;
    break;
  case '7':
    local_c = 7;
    break;
  case '8':
    local_c = 8;
    break;
  case '9':
    local_c = 9;
    break;
  default:
    local_c = 0;
    break;
  case 'A':
  case 'a':
    local_c = 10;
    break;
  case 'B':
  case 'b':
    local_c = 0xb;
    break;
  case 'C':
  case 'c':
    local_c = 0xc;
    break;
  case 'D':
  case 'd':
    local_c = 0xd;
    break;
  case 'E':
  case 'e':
    local_c = 0xe;
    break;
  case 'F':
  case 'f':
    local_c = 0xf;
  }
  return local_c;
}