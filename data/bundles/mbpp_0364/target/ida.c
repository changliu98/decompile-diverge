int __cdecl func0(const char *str)
{
  int flip_with_starting_character; // [rsp+4h] [rbp-Ch]

  flip_with_starting_character = get_flip_with_starting_character(str, 48);
  if ( flip_with_starting_character >= get_flip_with_starting_character(str, 49) )
    return get_flip_with_starting_character(str, 49);
  else
    return get_flip_with_starting_character(str, 48);
}