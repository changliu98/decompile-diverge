static int is_valid(void *ptr)
{
  return ptr == (void *) (unsigned long) ptr;
}