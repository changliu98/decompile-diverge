void __cdecl atomic_add(int i, volatile long *v)
{
    _InterlockedAdd((volatile signed __int32 *)v, i);
}