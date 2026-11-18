static void beep_print(struct line *line, char *buf, int len)
{
 if (l_strnstart("MSG ", 4, buf, len))
  line->print(line, " BEEP MSG");
 else if (l_strnstart("RPY ", 4, buf, len))
  line->print(line, " BEEP RPY");
 else if (l_strnstart("ERR ", 4, buf, len))
  line->print(line, " BEEP ERR");
 else if (l_strnstart("ANS ", 4, buf, len))
  line->print(line, " BEEP ANS");
 else if (l_strnstart("NUL ", 4, buf, len))
  line->print(line, " BEEP NUL");
 else if (l_strnstart("SEQ ", 4, buf, len))
  line->print(line, " BEEP SEQ");
 else if (l_strnstart("END ", 4, buf, len))
  line->print(line, " BEEP END");
 else
  line->print(line, " BEEP (payload or undecoded)");
}