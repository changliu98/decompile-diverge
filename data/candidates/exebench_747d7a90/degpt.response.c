/**
 * @brief Closes the write end of the pipe and updates the input file descriptor and counter.
 * 
 * @param fd_pipe Pointer to the pipe file descriptor array.
 * @param fd_in Pointer to the input file descriptor to be updated.
 * @param i Pointer to the counter to be incremented.
 */
void fork_child(int *pipe_fds, int *input_fd, int *counter)
{
    // Close the write end of the pipe in the child process
    close(pipe_fds[1]);
    
    // Assign the read end of the pipe to the input file descriptor
    *input_fd = *pipe_fds;
    
    // Increment the counter
    *counter = *counter + 1;
}