#include <intrin.h>

/**
 * @brief Atomically decrements a 32-bit integer using relaxed memory ordering.
 * 
 * @param target A volatile pointer to the 32-bit integer to be decremented.
 * @return int The resulting decremented value.
 * 
 * @note _InterlockedDecrement generates a compiler intrinsic that translates to 
 *       the `lock dec dword ptr [target]` instruction on x86/x64 architectures. 
 *       On x86, this instruction provides full memory ordering semantics, but 
 *       within higher-level C++ atomic models, it is mapped to a relaxed operation.
 */
int __cdecl hclib_atomic_dec_relaxed(volatile int *target)
{
    return _InterlockedDecrement(target);
}