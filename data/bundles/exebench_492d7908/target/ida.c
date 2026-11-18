void __cdecl edosk2674_smsc_outw(unsigned __int16 d, volatile unsigned __int16 *a)
{
  *a = (d << 8) | ((int)d >> 8);
}