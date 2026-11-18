for abs

void __cdecl func0(const int *game, const int *guess, int *out, int length)
{
  for (int i = 0; i < length; ++i)
  {
    out[i] = abs(game[i] - guess[i]);
  }
}