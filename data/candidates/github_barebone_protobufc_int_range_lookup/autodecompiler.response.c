int
int_range_lookup (unsigned int range_count,
      struct range *range,
      int value)
{
  unsigned int start, end, mid;
  int result;

  if (range_count == 0)
    return -1;

  start = 0;
  end = range_count;

  while (1)
    {
      if (end > 1)
 {
   mid = start + (end / 2);
   if (value < range[mid].min)
     end = mid - start;
   else if (value >= range[mid].min + (range[mid + 1].max - range[mid].max))
     {
       unsigned int new_start = mid + 1;
       end = start + end - new_start;
       start = new_start;
     }
   else
     {
       result = value - range[mid].min + range[mid].max;
       break;
     }
 }
      else if (end > 0)
 {
   int orig_min = range[start].max;
   int range_size = range[start + 1].max - orig_min;

   if (value >= range[start].min && value < range[start].min + range_size)
     {
       result = value - range[start].min + orig_min;
       break;
     }
 }
      else
 {
   result = -1;
   break;
 }
    }

  return result;
}