int MPI_Group_incl(group, n, ranks, newgroup)
int group, n, *ranks, *newgroup;
{
  int dummy[100];
  if (n > 0)
    *newgroup = 0;
  else
    *newgroup = group;
  return 0;
}