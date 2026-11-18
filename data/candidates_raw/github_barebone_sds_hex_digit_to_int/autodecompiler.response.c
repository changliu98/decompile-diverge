int hexval(char c)
{
 int x;
 switch(c)
 {
  case '0': x=0;break;
  case '1': x=1;break;
                case '2': x=2;break;
                case '3': x=3;break;
                case '4': x=4;break;
                case '5': x=5;break;
                case '6': x=6;break;
                case '7': x=7;break;
                case '8': x=8;break;
                case '9': x=9;break;
                case 'A': case 'a': x=10;break;
                case 'B': case 'b': x=11;break;
                case 'C': case 'c': x=12;break;
                case 'D': case 'd': x=13;break;
                case 'E': case 'e': x=14;break;
                case 'F': case 'f': x=15;break;
  default: x=0;
 }
 return x;
}