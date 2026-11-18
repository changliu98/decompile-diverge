int atomic_fetch_and (void)
{
 int x = 0;
 int y = 0;
 int z = 0;

 x = andl(&y, z);
 return 0;
}