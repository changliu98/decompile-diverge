
int ExtractRnick(char *Rnick, char *incoming_msg)
{
 int k=0;

 if(*incoming_msg == ':') incoming_msg++;

 while(*incoming_msg!='!' && *incoming_msg!=0) {
  Rnick[k]=*incoming_msg;
  incoming_msg++;
  k++;
 }
 Rnick[k]=0;

 if (*Rnick < '0') return 0;
 else return 1;
}
