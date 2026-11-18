char * func0(char *string)

{
  int j;
  int i;
  int found [10];
  int count;
  char vowels [11];
  char *string_local;
  char *local_10;
  
  vowels._0_8_ = s_AEIOUaeiou_00102004._0_8_;
  vowels._8_2_ = s_AEIOUaeiou_00102004._8_2_;
  vowels[10] = s_AEIOUaeiou_00102004[10];
  count = 0;
  memset(found,0,0x28);
  i = 0;
  do {
    if (string[i] == '\0') {
      if (count < 5) {
        local_10 = "not accepted";
      }
      else {
        local_10 = "accepted";
      }
      return local_10;
    }
    for (j = 0; j < 10; j = j + 1) {
      if ((string[i] == vowels[j]) && (found[j] == 0)) {
        found[j] = 1;
        count = count + 1;
        break;
      }
    }
    i = i + 1;
  } while( true );
}