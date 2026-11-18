void next(int *min, int *sec, int frames_per_sec)
{
 (*sec)++;
 if (*sec == frames_per_sec) {
  (*sec) = 0;
  (*min)++;
 }
}