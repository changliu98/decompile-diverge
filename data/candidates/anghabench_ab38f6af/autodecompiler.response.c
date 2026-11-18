static int ad7192_get_temp_scale(int unipolar)
{
 return unipolar ? 5630 : 2815;
}