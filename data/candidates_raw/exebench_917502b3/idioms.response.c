int update_alpha_beta(int score, int *alpha, int *beta, int max)
{
  if (max && score > *alpha)
    *alpha = score;
  else if (!max && score < *beta)
    *beta = score;
  return *beta > *alpha ? 1 : 0;
}