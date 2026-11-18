void __cdecl reset_request(RespRequest *request)
{
  // Guard against NULL pointer dereference
  if ( !request )
    return;

  // Reset parsing state and argument counters
  request->state     = 0;
  request->cur_argc  = 0;
  request->argc      = 0;

  // Free the dynamically allocated argument vector if it exists
  if ( request->argv )
    free(request->argv);
    
  request->argv      = NULL; // Using NULL for clarity over 0LL

  // Reset buffer pointers and sizes
  request->used_size = 0;
  request->pos       = 0;
  request->skip_str  = 0;
}