unsigned int __cdecl ad7192_get_temp_scale(bool unipolar)
{
  if (unipolar)
    return 5630;
  
  return 2815;
}