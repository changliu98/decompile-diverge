void __cdecl sdsrange(sds s, ssize_t start, ssize_t end)
{
    ssize_t len = sdslen(s);
    
    // Only process if the string is not empty
    if (len == 0)
        return;

    // Handle negative start index (count from the end)
    if (start < 0)
    {
        start += len;
        if (start < 0)
            start = 0;
    }

    // Handle negative end index (count from the end)
    if (end < 0)
    {
        end += len;
        if (end < 0)
            end = 0;
    }

    // Calculate the new length of the substring
    size_t newlen;
    if (start > end)
    {
        newlen = 0;
    }
    else
    {
        newlen = end - start + 1;
        
        // Clamp the length to ensure it doesn't exceed the string bounds
        if (start >= len)
        {
            newlen = 0;
        }
        else if (end >= len)
        {
            newlen = len - start;
        }
    }

    // Shift the substring to the beginning of the buffer if necessary
    if (start > 0 && newlen > 0)
    {
        memmove(s, s + start, newlen);
    }

    // Null-terminate and update the string's recorded length
    s[newlen] = 0;
    sdssetlen(s, newlen);
}