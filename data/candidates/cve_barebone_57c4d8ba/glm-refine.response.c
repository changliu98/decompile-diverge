int __cdecl compile_get_env(char_u **arg, cctx_T *cctx)
{
  char_u *start;
  int len;
  char_u *name;
  int ret;

  // Save the start of the environment variable name and advance the parser pointer
  start = *arg;
  (*arg)++;

  // Parse the length of the valid environment variable name
  len = get_env_len(arg);

  if (len > 0)
  {
    // Allocate a null-terminated copy of the variable name.
    // Note: len + 1 is passed to vim_strnsave to accommodate the null terminator.
    name = vim_strnsave(start, len + 1);
    
    // Generate the bytecode instruction to load the environment variable at runtime
    ret = generate_LOAD(cctx, ISN_LOADENV, 0, name, &t_string);
    
    // Free the temporary string buffer
    vim_free(name);
    
    return ret;
  }
  else
  {
    // Syntax error: Invalid or empty environment variable name.
    // The error message points back to the '$' character (start - 1).
    semsg("E1002: Syntax error at %s", (const char *)start - 1);
    return 0;
  }
}