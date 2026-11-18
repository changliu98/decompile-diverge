int subprocess_error_from_errno(int err) {
 int ret;
 switch(err) {
 case 2:
 case 12:
 case 20:
 case 30:
  ret = -4;
  break;
 case 1:
 case 13:
 case 21:
  ret = -5;
  break;
 case 3:
 case 14:
 case 22:
 case 31:
  ret = -6;
  break;
 default:
  ret = -1;
 }
 return ret;
}