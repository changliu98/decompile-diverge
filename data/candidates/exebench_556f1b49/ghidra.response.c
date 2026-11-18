int MPI_Group_incl(int group,int n,int *ranks,int *newgroup)

{
  int *newgroup_local;
  int *ranks_local;
  int n_local;
  int group_local;
  
  if (n < 1) {
    *newgroup = group;
  }
  else {
    *newgroup = 0;
  }
  return 0;
}