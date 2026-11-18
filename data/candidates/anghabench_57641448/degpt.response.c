int ui_select(int in)
{
  // Check if the global TCP socket is currently uninitialized (zero)
  if (global_tcp_socket == 0) {
    // Assign the input socket descriptor to the global TCP socket variable
    global_tcp_socket = in;
  }
  // Always return success
  return 1;
}