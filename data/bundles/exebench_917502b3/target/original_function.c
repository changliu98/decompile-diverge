static int alphabeta_cutoff (int score, int *alpha, int *beta, int max)
{
 if (max && score > *alpha) {
  *alpha = score;
 } else if (!max && score < *beta) {
  *beta = score;
 }
 if (*beta <= *alpha) {
  return 1;
 }

 return 0;
}