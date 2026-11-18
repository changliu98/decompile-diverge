unsigned char fsp_test_invert_cmd(unsigned char c)
{
 unsigned char ret;

 switch(c)
 {
  case 0xE9:
  case 0xEE:
  case 0xF2:
  case 0xFF:
   ret = c ^ 0xFF;
   break;
  default:
   ret = c;
 }

 return ret;
}