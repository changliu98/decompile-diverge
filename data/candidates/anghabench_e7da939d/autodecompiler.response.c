static char *test_to_str(int type)
{
 char *str;
 switch (type) {
 case SENDMSG:
  str = "sendmsg";
  break;
 case SENDPAGE:
  str = "sendpage";
  break;
 default:
  str = "unknown";
 }
 return str;
}