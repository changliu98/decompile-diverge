int
nsvg__getArgsPerElement(char c)
{
 int ret;

 switch(c) {
 case 'H':
 case 'V':
 case 'h':
 case 'v':
  ret = 1;
  break;
 case 'L':
 case 'M':
 case 'T':
 case 'l':
 case 'm':
 case 't':
  ret = 2;
  break;
 case 'Q':
 case 'S':
 case 'q':
 case 's':
  ret = 4;
  break;
 case 'C':
 case 'c':
  ret = 6;
  break;
 case 'A':
 case 'a':
  ret = 7;
  break;
 case 'Z':
 case 'z':
  ret = 0;
  break;
 default:
  ret = -1;
 }

 return ret;
}