int __cdecl deo_pipe(int *rend, int *wend)
{
  int in[2]; // [rsp+0h] [rbp-20h] BYREF
  int *wenda; // [rsp+8h] [rbp-18h]
  int *renda; // [rsp+10h] [rbp-10h]

  renda = rend;
  wenda = wend;
  if ( pipe(in) )
    return *__errno_location();
  *renda = in[0];
  *wenda = in[1];
  return 0;
}