int atomic32_increment(int *dest)
{
 int r;


 r = __sync_add_and_fetch(dest, 1U);






 return r;
}