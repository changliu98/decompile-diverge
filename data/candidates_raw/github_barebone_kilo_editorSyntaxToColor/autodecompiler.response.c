int
get_color(int color)
{
 int ret;

 switch(color) {
 case COLOR_BLACK:
 case COLOR_RED:
  ret = '$';
  break;
 case COLOR_GREEN:
  ret = '!';
  break;
 case COLOR_YELLOW:
  ret = ' ';
  break;
 case COLOR_BLUE:
  ret = '#';
  break;
 case COLOR_MAGENTA:
  ret = '\037';
  break;
 case COLOR_CYAN:
  ret = '"';
  break;
 case COLOR_WHITE:
 default:
  ret = '%';
 }
 return ret;
}