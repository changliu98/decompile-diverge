void __cdecl atomic_or_long(_Atomic unsigned __int64 *v1, unsigned __int64 v2)
{
    atomic_fetch_or_explicit(v1, v2, memory_order_seq_cst);
}