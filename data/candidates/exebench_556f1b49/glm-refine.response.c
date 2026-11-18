int __cdecl MPI_Group_incl(int group, int n, int *ranks, int *newgroup)
{
    // If the number of ranks to include is zero or negative, 
    // the "new" group is effectively the same as the original group.
    // Otherwise, initialize the new group to 0 (MPI_GROUP_EMPTY or null).
    if (n <= 0)
    {
        *newgroup = group;
    }
    else
    {
        *newgroup = 0;
    }

    return 0; // MPI_SUCCESS
}