void opl3_set_con(struct opl3_channel *ch, unsigned char con)
{
  ch->fb = (con & 0x0e) >> 1;
  ch->con = (con & 0x01);
  opl3_set_amod(ch);
  if (ch->chip->newm)
  {
    ch->cha = (con & 0x10) ? -1 : 0;
    ch->chb = (con & 0x20) ? -1 : 0;
    ch->chc = (con & 0x40) ? -1 : 0;
    ch->chd = (con & 0x80) ? -1 : 0;
  }
  else
  {
    ch->chb = -1;
    ch->cha = -1;
    ch->chd = 0;
    ch->chc = 0;
  }
}