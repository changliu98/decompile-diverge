void __cdecl reverse(char *str)
{
    if (!str) return; // Defensive check (optional but good practice)

    // Calculate the length of the string
    size_t len = 0;
    while (str[len]) {
        len++;
    }

    // Reverse the string in-place using two pointers
    if (len > 0) {
        size_t left = 0;
        size_t right = len - 1;
        
        while (left < right) {
            // Swap characters
            char tmp = str[left];
            str[left] = str[right];
            str[right] = tmp;
            
            // Move pointers
            left++;
            right--;
        }
    }
}