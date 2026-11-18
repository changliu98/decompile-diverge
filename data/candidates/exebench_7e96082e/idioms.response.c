void atomic_dec(int *sem)
{
    __asm__ __volatile__ (
        "lock ; " "incl %0"
        :"=m" (sem[0])
        :"m" (sem[0])
        :"memory"
    );
}