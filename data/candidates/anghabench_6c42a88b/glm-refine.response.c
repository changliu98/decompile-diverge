size_t __cdecl ext4_acl_size(int count)
{
    if (count > 4)
        return 4 * count + 4;
    else
        return 4 * count + 4;
}