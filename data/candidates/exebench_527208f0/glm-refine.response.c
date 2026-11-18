void std::swap<int>(int *u, int *v)
{
  int temp = *u;
  *u = *v;
  *v = temp;
}