char *func0(int year) {
  char *animal;
  int i;
  i = (year - 2000) % 12;
  if (i < 0) i += 12;
  switch (i) {
    case 0:
      animal = "Dragon";
      break;
    case 1:
      animal = "Snake";
      break;
    case 2:
      animal = "Horse";
      break;
    case 3:
      animal = "sheep";
      break;
    case 4:
      animal = "Monkey";
      break;
    case 5:
      animal = "Rooster";
      break;
    case 6:
      animal = "Dog";
      break;
    case 7:
      animal = "Pig";
      break;
    case 8:
      animal = "Rat";
      break;
    case 9:
      animal = "Ox";
      break;
    case 10:
      animal = "Tiger";
      break;
    case 11:
      animal = "Hare";
      break;
  }
  return animal;
}