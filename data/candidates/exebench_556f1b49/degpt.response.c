int MPI_Group_incl(int source_group, int num_ranks, int *rank_list, int *result_group)
{
    // If the number of ranks is less than 1, set the new group to the original group
    if (num_ranks < 1) {
        *result_group = source_group;
    }
    // Otherwise, set the new group to 0 (indicating an invalid or empty group)
    else {
        *result_group = 0;
    }
    // Return success status
    return 0;
}