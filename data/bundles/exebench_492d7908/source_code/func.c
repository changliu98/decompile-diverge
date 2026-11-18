
static inline void edosk2674_smsc_outw(
 unsigned short d,
 volatile unsigned short *a
 )
{
 *a = (d >> 8) | (d << 8);
}
