int fun(int *a)
{
 int y;
 int x = 0;
 int temp;

 switch(*a / 10) {
  case 9: x = 6; break;
  case 8: x = 6; break;
  case 7: x = 7; break;
  case 6: x = 5; break;
  case 5: x = 5; break;
  case 4: x = 5; break;
  case 3: x = 6; break;
  case 2: x = 6; break;
  case 1:
   switch(*a) {
    case 19: x = 8; break;
    case 18: x = 8; break;
    case 17: x = 9; break;
    case 16: x = 7; break;
    case 15: x = 7; break;
    case 14: x = 8; break;
    case 13: x = 8; break;
    case 12: x = 6; break;
    case 11: x = 6; break;
    case 10: x = 3;
    default: *a = 0;
   }
   temp = x;
   break;
  case 0: temp = 0; break;
  default: *a %= 10;
 }
 return temp;
}