void __cdecl set_page_data(int potval, char *buf)
{
  *(_DWORD *)buf = potval;
}