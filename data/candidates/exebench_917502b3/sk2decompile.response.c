int alphabeta_cutoff(int score, int *alpha, int *beta, int maximizing_player) {
  if (maximizing_player && score > *alpha)
    *alpha = score;
  else if (!maximizing_player && score < *beta)
    *beta = score;
  return *alpha >= *beta;
}