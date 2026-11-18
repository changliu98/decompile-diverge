size_t __cdecl ext4_acl_size(int count)
{
  if ( count > 4 )
    return 4LL * (count - 4) + 20;
  else
    return 4LL * count + 4;
}