int
func0 (int cmd)
{
  int canonical;
  if (cmd == 0) { canonical = 1; }
  else if (cmd <= 2) { canonical = cmd; }
  else if (cmd == 3) { canonical = 6; }
  else if (cmd == 4) { canonical = 4; }
  else { canonical = 0; }
  return canonical;
}