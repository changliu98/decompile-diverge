int nsvg__parseUnits(char *unit)
{
  int type;

  if ((strncmp(unit,"px",2)) == 0) {
    type = 1;
  } else if ((strncmp(unit,"pt",2)) == 0) {
    type = 2;
  } else if ((strncmp(unit,"pc",2)) == 0) {
    type = 3;
  } else if ((strncmp(unit,"mm",2)) == 0) {
    type = 4;
  } else if ((strncmp(unit,"cm",2)) == 0) {
    type = 5;
  } else if ((strncmp(unit,"in",2)) == 0) {
    type = 6;
  } else if ((strncmp(unit,"%",1)) == 0) {
    type = 7;
  } else if ((strncmp(unit,"em",2)) == 0) {
    type = 8;
  } else if ((strncmp(unit,"ex",2)) == 0) {
    type = 9;
  } else {
    switch (unit[0]) {
      case 'P': type = 1; break;
      case 'L': type = 2; break;
      case 'C': type = 3; break;
      case 'M': type = 4; break;
      case 'I': type = 5; break;
      case 'X': type = 6; break;
      case '%': type = 7; break;
      case 'E': type = 8; break;
      case 'R': type = 9; break;
      default: type = 0; break;
    }
  }

  return(type);
}