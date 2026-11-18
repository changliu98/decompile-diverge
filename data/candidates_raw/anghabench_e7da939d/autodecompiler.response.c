static char *get_send_type(int type)
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