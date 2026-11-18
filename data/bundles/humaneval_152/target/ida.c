void __cdecl func0(int *game, int *guess, int *out, int length)
{
  int i; // [rsp+0h] [rbp-20h]

  for ( i = 0; i < length; ++i )
    out[i] = abs(game[i] - guess[i]);
}