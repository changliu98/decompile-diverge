void WordToHex(unsigned int Number, char* String) {
        int i;
        unsigned int Temp, Module;
        Temp=Number;
        for(i=3; i>=0; i--) {
  Module=Temp&15;
  if(Module<10) String[i]=Module+'0'; else String[i]=Module+'A'-10;
  Temp=(Temp>>4)&0xfff;
        }
        String[4]='\0';
}