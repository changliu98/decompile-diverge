static int
get_port(int interface, int port)
{
 int ret;
 long ifnum = interface;

 switch (ifnum) {
 case 0:
  ret = port + 0;
  break;
 case 1:
  ret = port + 16;
  break;
 case 2:
  ret = port + 32;
  break;
 case 3:
  ret = port + 36;
  break;
 case 4:
  ret = port + 40;
  break;
 case 5:
  ret = port + 44;
  break;
 default:
  ret = -1;
 }
 return ret;
}