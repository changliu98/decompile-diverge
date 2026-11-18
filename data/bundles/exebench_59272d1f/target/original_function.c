void bo_backoff(int *bwait, int cap) {
  for(int i = *bwait; i; i--);
  *bwait = (((*bwait*2) < (cap)) ? (*bwait*2) : (cap));
}