unsigned int __cdecl ad7192_get_temp_scale(bool unipolar)
{
  unsigned int result; // eax

  result = 2815;
  if ( unipolar )
    return 5630;
  return result;
}