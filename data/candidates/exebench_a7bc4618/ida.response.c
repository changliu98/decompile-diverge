void __cdecl remove_line_ending(char *text, char ending)
{
  char *texta; // [rsp+8h] [rbp-8h]

  texta = strrchr(text, ending);
  if ( texta )
    *texta = 0;
}