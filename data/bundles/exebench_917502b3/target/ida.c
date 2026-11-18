int __cdecl alphabeta_cutoff(int score, int *alpha, int *beta, int max)
{
  if ( max && score > *alpha )
  {
    *alpha = score;
  }
  else if ( !max && score < *beta )
  {
    *beta = score;
  }
  return *beta <= *alpha;
}