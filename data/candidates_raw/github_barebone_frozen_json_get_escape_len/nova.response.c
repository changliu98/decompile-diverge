static int func0(const char *z, int n){
  int j;
  int c = z[0];

  
  switch( c ){
    case 'A': j = 1; break;
    case 'I': j = 2; break;
    case 'S': j = 3; break;
    case 'T': j = 4; break;
    case 'F': j = 5; break;
    case 'W': j = 6; break;
    default:  j = -1; break;
  }

  if( j>=0 ){
    int i = -1;
    if( n<7 ){
      i = -2;
    }else if(!isConsonant(z[1]) ){
      i = 0;
    }else if(!isConsonant(z[2]) ){
      i = 0;
    }else if(!isConsonant(z[3]) ){
      i = 0;
    }else if(!isConsonant(z[4]) ){
      i = 0;
    }else{
      i = 1;
    }
    return i;
  }

  int i = -1;
  if( n<3 ){
    i = -2;
  }else{
    i = 1;
  }
  return i;
}