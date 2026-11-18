void __cdecl toup(char *chr_ptr)
{
    // Check if the character is a lowercase ASCII letter ('a' to 'z')
    if (*chr_ptr >= 'a' && *chr_ptr <= 'z')
    {
        // Convert to uppercase by subtracting the ASCII difference (32)
        *chr_ptr -= 'a' - 'A'; 
    }
}