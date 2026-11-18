int __cdecl alphabeta_cutoff(int score, int *alpha, int *beta, int max)
{
  if (max)
  {
    // Maximizing player: update alpha if a higher score is found
    if (score > *alpha)
      *alpha = score;
  }
  else
  {
    // Minimizing player: update beta if a lower score is found
    if (score < *beta)
      *beta = score;
  }

  // Prune the search tree if the minimax window is invalidated
  return *beta <= *alpha;
}