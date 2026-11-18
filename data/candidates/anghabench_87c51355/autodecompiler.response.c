static size_t
spc_used(size_t w, size_t r, size_t size)
{
 int diff;
 size_t space;

 diff = w - r;
 if (diff >= 0) {
  space = (size_t)diff;
 } else {
  space = size + diff;
 }

 return (space);
}