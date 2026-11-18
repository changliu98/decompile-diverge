int editorSyntaxToColor(int hl) {
  switch (hl) {
    case 2:
    case 3:
      return 36;
    case 4:
      return 33;
    case 5:
      return 32;
    case 6:
      return 35;
    case 7:
      return 31;
    case 8:
      return 34;
    default:
      return 37;
  }
}