void OPLL_Reset(OPLL *opll, int type)
{
 unsigned int i ;

 memset(opll,0,sizeof(OPLL));

 opll->type = type;
 if( type == 0x01 )
 {
  opll->mask = 0x20 ;
  opll->adpcm = (unsigned char*)0x80 ;
 }
 switch(type)
 {
 case 0x01 :
  opll->patch = &patch_ds1001 ;
  break ;
 case 0x03 :
 case 0x04 :
  opll->patch = &patch_ymf281 ;
  break ;
 case 0x06 :
  opll->patch = &patch_ym2423 ;
  break ;
 case 0x00 :
 case 0x02 :
 case 0x05 :
 default :
  opll->patch = &patch_ym2413 ;
 }

 for( i = 0 ; i < 19 ; i++ )
 {
  opll->r[i+(0x2d)] = 0x03 ;
  opll->r[i+(0x3f)] = 0x7f ;
  opll->r[(0x64)] = 0x7f ;
 }
 opll->r[(0x65)] = 0x06 ;

}