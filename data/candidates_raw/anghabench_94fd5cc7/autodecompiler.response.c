static int
midi_to_bend(unsigned char note)
{
 int bend = 0;
 note &= 0x7f;

 switch (note) {
 case 108: bend = 11; break;
 case 96: bend = 10; break;
 case 72: bend = 9; break;
 case 48: bend = 8; break;
 case 36: bend = 7; break;
 case 24: bend = 6; break;
 case 18: bend = 5; break;
 case 12: bend = 4; break;
 case 22: bend = 3; break;
 case 11: bend = 2; break;
 case 4: bend = 1; break;
 case 2: bend = 0; break;
 }

 return bend;
}