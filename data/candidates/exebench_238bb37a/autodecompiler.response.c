static size_t
incr(size_t *total, size_t size)
{
 size_t old = *total;
 size_t new = old + size;

 *total = new;
 return old;
}