double func0(double *numbers,int length)

{
  double *pdVar1;
  double dVar2;
  undefined8 uVar3;
  bool bVar4;
  void *__ptr;
  double result;
  double temp;
  int j_2;
  int i_2;
  int j_1;
  int found;
  int i_1;
  int uniq_length;
  double *uniq_items;
  int j;
  int i;
  int count;
  int length_local;
  double *numbers_local;
  double local_10;
  
  if (length < 2) {
    local_10 = DAT_00102008;
  }
  else {
    count = 0;
    for (i = 0; j = i, i < length; i = i + 1) {
      do {
        j = j + 1;
        if (length <= j) goto LAB_00101281;
      } while ((numbers[j] != numbers[i]) || (NAN(numbers[j]) || NAN(numbers[i])));
      count = count + 1;
LAB_00101281:
    }
    if ((length == 2) && (count == 1)) {
      local_10 = DAT_00102008;
    }
    else {
      __ptr = malloc((long)length << 3);
      uniq_length = 0;
      for (i_1 = 0; i_1 < length; i_1 = i_1 + 1) {
        bVar4 = false;
        for (j_1 = 0; j_1 < uniq_length; j_1 = j_1 + 1) {
          dVar2 = *(double *)((long)__ptr + (long)j_1 * 8);
          if ((dVar2 == numbers[i_1]) && (!NAN(dVar2) && !NAN(numbers[i_1]))) {
            bVar4 = true;
            break;
          }
        }
        if (!bVar4) {
          *(double *)((long)__ptr + (long)uniq_length * 8) = numbers[i_1];
          uniq_length = uniq_length + 1;
        }
      }
      for (i_2 = 0; j_2 = i_2, i_2 < uniq_length; i_2 = i_2 + 1) {
        while (j_2 = j_2 + 1, j_2 < uniq_length) {
          dVar2 = *(double *)((long)__ptr + (long)i_2 * 8);
          pdVar1 = (double *)((long)__ptr + (long)j_2 * 8);
          if (*pdVar1 <= dVar2 && dVar2 != *pdVar1) {
            uVar3 = *(undefined8 *)((long)__ptr + (long)i_2 * 8);
            *(undefined8 *)((long)__ptr + (long)i_2 * 8) =
                 *(undefined8 *)((long)__ptr + (long)j_2 * 8);
            *(undefined8 *)((long)__ptr + (long)j_2 * 8) = uVar3;
          }
        }
      }
      local_10 = *(double *)((long)__ptr + 8);
      free(__ptr);
    }
  }
  return local_10;
}