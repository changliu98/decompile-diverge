// The function signature uses '__cdecl', which is standard for C. 
// We rename the function and parameter to reflect its behavior.
void __cdecl ZeroOutInt(int *pIntValue)
{
    // Dereference the pointer and assign 0 to the pointed-to integer.
    *pIntValue = 0;
}