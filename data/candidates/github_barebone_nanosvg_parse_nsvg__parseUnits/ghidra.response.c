int nsvg__parseUnits(char *units)

{
  char *units_local;
  int local_c;
  
  if ((*units == 'p') && (units[1] == 'x')) {
    local_c = 1;
  }
  else if ((*units == 'p') && (units[1] == 't')) {
    local_c = 2;
  }
  else if ((*units == 'p') && (units[1] == 'c')) {
    local_c = 3;
  }
  else if ((*units == 'm') && (units[1] == 'm')) {
    local_c = 4;
  }
  else if ((*units == 'c') && (units[1] == 'm')) {
    local_c = 5;
  }
  else if ((*units == 'i') && (units[1] == 'n')) {
    local_c = 6;
  }
  else if (*units == '%') {
    local_c = 7;
  }
  else if ((*units == 'e') && (units[1] == 'm')) {
    local_c = 8;
  }
  else if ((*units == 'e') && (units[1] == 'x')) {
    local_c = 9;
  }
  else {
    local_c = 0;
  }
  return local_c;
}