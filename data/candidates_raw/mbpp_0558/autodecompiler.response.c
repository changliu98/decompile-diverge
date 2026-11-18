int subtraktion(int zahl1, int zahl2){
 int differenz;
 differenz = abs(zahl1 - zahl2);
 int subtraktionszahl = 0;
 while(1){
  if(differenz > 0){
   subtraktionszahl = subtraktionszahl + differenz % 10;
   differenz = differenz / 10;
  }else{
   return subtraktionszahl;
  }
 }
}