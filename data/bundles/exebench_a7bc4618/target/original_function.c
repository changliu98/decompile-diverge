void remove_line_ending(char *text, char ending) {
  text = strrchr(text, ending);
  if(text)
    *text = 0;
}