static int hexval(int c)
{
 int ret;

 switch(c) {
 case '0': ret = 0; break;
 case '1': ret = 1; break;
 case '2': ret = 2; break;
 case '3': ret = 3; break;
 case '4': ret = 4; break;
 case '5': ret = 5; break;
 case '6': ret = 6; break;
 case '7': ret = 7; break;
 case '8': ret = 8; break;
 case '9': ret = 9; break;
 case 'A': case 'a': ret = 10; break;
 case 'B': case 'b': ret = 11; break;
 case 'C': case 'c': ret = 12; break;
 case 'D': case 'd': ret = 13; break;
 case 'E': case 'e': ret = 14; break;
 case 'F': case 'f': ret = 15; break;
 default: ret = -1;
 }
 return ret;
}