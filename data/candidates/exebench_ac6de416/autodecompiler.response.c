void adjust_mode_num(int *hue)
{
 if (*hue > 9) {
  *hue = 9;
 } else if (*hue < 0) {
  *hue = 0;
 }
}