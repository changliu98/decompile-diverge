// Creates a pipe and returns the file descriptors for reading and writing
int deo_pipe(int *read_fd, int *write_fd)
{
    int pipe_fds[2]; // Array to hold the two file descriptors for the pipe
    int pipe_result = pipe(pipe_fds); // Create the pipe; returns 0 on success, -1 on error
    if (pipe_result == 0) {
        *read_fd = pipe_fds[0]; // Assign the read end of the pipe to rend
        *write_fd = pipe_fds[1]; // Assign the write end of the pipe to wend
    }
    return pipe_result; // Return 0 on success, -1 on error
}