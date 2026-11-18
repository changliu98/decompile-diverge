void put_num(unsigned short* dst,unsigned int num,unsigned char len)
{
 if(len>=5) *dst++=(0x0100|(((0)&7)<<10)|0x2000)|'0'-32+(num/10000)%10;
 if(len>=4) *dst++=(0x0100|(((0)&7)<<10)|0x2000)|'0'-32+(num/1000)%10;
 if(len>=3) *dst++=(0x0100|(((0)&7)<<10)|0x2000)|'0'-32+(num/100)%10;
 if(len>=2) *dst++=(0x0100|(((0)&7)<<10)|0x2000)|'0'-32+(num/10)%10;
 if(len>=1) *dst++=(0x0100|(((0)&7)<<10)|0x2000)|'0'-32+ num %10;
}