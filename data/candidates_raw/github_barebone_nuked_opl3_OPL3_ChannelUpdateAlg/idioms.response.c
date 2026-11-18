void opl3_set_con(struct opl3_channel *ch)
{
  ch->alg = ch->con;
  if (ch->chip->newm) {
    if (ch->chtype == 1) {
      ch->pair->alg = (ch->con * 2) | (ch->pair->con * 1) | 4;
      ch->alg = 8;
      opl3_set_con(ch->pair);
    } else if (ch->chtype == 2) {
      ch->alg = (ch->con * 2) | (ch->pair->con * 1) | 4;
      ch->pair->alg = 8;
    }
  }
  opl3_set_con(ch);
}