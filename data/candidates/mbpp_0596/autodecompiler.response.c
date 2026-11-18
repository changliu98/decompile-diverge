static size_t
func0(struct s *s, size_t n)
{
 size_t i, total_size = 0;

 for (i = 0; ; i++) {
  if (i < n) {
   total_size += sizeof(struct s);
   i++;
  } else {
   break;
  }
 }

 return total_size;
}