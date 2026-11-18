int alphabeta_cutoff(int score,int *alpha,int *beta,int max)

{
  int max_local;
  int *beta_local;
  int *alpha_local;
  int score_local;
  uint local_c;
  
  if ((max == 0) || (score <= *alpha)) {
    if ((max == 0) && (score < *beta)) {
      *beta = score;
    }
  }
  else {
    *alpha = score;
  }
  local_c = (uint)(*beta <= *alpha);
  return local_c;
}