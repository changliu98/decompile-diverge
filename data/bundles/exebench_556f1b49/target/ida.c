int __cdecl MPI_Group_incl(int group, int n, int *ranks, int *newgroup)
{
  if ( n <= 0 )
    *newgroup = group;
  else
    *newgroup = 0;
  return 0;
}