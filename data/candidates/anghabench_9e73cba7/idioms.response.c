static int uasm_in_compat_space_p(void *ptr)
{
  return ptr == (void *) (unsigned long) ptr;
}