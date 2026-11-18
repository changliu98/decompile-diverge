int tomoyo_invalid(wchar_t wc)
{
 unsigned char c = wc;
 return ((c == 0) ? 0 : ((c <= 32) || (c >= 127)));
}