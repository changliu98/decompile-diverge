void add(int x, int y, int z, struct pair *result) {
 if (y > z) {
  result->a = x + z;
  result->b = 0;
  return;
 }
 result->a = x + y;
 result->b = z - y;
}