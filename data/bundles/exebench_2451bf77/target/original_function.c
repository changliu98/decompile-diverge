void spin_unlock(int volatile* p)
{
 asm volatile ("");
 *p = 0;
}