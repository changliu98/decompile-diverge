// Swaps the values of two integers pointed to by pa and pb.
void __cdecl std::swap<int>(int *pa, int *pb)
{
  int t = *pa;
  *pa = *pb;
  *pb = t;
}