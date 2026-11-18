int EPD_1_5_6_Gray_Delta(int index, int *direction)
{
 int dir_in = index % 2;
 if (direction) *direction = dir_in;
 return (index + dir_in) / 2;
}