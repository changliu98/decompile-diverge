static size_t func0(const void* src, size_t srcSize)
{
    const BYTE* ip = (const BYTE*)src;
    size_t length = 0;
    size_t i = 0;
    while (i < srcSize) {
        length += (ip[i+1] << 8) + ip[i];
        i += 2;
    }
    return length;
}