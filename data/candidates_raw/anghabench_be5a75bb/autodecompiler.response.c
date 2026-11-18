int quicktime_quantize4(int number)
{
 return (number + 3 - ((number) & 3));
}