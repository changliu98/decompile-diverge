void __cdecl f(int *p)
{
    p[2] = p[0]; // Copy the 1st element (index 0) to the 3rd element (index 2)
    p[3] = p[1]; // Copy the 2nd element (index 1) to the 4th element (index 3)
}