/**
 * @brief Closes a socket and invalidates the pointer to prevent reuse (use-after-free).
 * 
 * @param sockfd A pointer to the socket file descriptor to be closed.
 * @return int The return value of the underlying close() syscall (0 on success, -1 on error).
 */
int __cdecl socket_close_(int *sockfd)
{
  // Save the original file descriptor
  int fd = *sockfd;
  
  // Invalidate the file descriptor to prevent accidental use-after-close
  *sockfd = -1;
  
  // Close the socket
  return close(fd);
}