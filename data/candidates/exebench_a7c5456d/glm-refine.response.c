intptr_t __cdecl atomic_fetch_add(intptr_t *object, intptr_t operand)
{
    // _InterlockedExchangeAdd is the standard MSVC intrinsic for atomic fetch-add on x86/x64.
    // It guarantees atomicity, matching the function's name and intended semantics.
    return _InterlockedExchangeAdd(object, operand);
}