/**
 * @brief Retrieves the rank of the calling process within the communicator.
 *
 * @param a The communicator handle (unused in this stub implementation).
 * @param b Pointer to an integer where the rank will be stored.
 */
void MPI_Comm_rank(int comm, int *rank)
{
    // Assign rank 0 to the calling process
    *rank = 0;
}