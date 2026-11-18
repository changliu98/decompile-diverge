int __cdecl func0(int a)
{
    // Multiplication by a power of 2 is typically optimized to a bitwise left shift 
    // in assembly (e.g., shl/sal). This reflects the underlying architecture's instruction.
    return a << 2;
}