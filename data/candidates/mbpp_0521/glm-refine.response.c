bool __cdecl func0(int x, int y, int z)
{
  // Checks if all three arguments are mutually distinct (no duplicates).
  return x != y && y != z && z != x;
}