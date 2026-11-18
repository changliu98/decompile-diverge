int error(int *ptr)
{
    // Increment the value pointed to by x by 1
    *ptr += 1;
    // Return the updated value pointed to by x
    return *ptr;
}