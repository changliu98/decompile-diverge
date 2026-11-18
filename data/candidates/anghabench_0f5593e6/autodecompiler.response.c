char *cause_excode_text( int cause )
{
 return cause_excode_text[(cause&0x7C)>>2];
}