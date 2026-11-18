int
fdd_size_id(int srt, int end, int size)
{
 int min, max, ret;

 if (srt < end) {
  min = srt;
  max = end;
 } else {
  min = end;
  max = srt;
 }

 if (size >= max)
  ret = ((size + (max - 1)) / max);
 else if (!size)
  ret = 0;
 else if (size == min)
  ret = 1;
 else
  ret = 2;

 return(ret);
}