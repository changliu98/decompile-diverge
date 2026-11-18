void opl2_set_ch_con(struct opl2_channel *ch)
{
  if (ch->chtype == 1) {
    if (ch->ch_num == 7 || ch->ch_num == 8) {
      ch->slotz[0]->mod = &ch->chip->zeromod;
      ch->slotz[1]->mod = &ch->chip->zeromod;
    }
    else {
      if (ch->con == 0) {
        ch->slotz[0]->mod = &ch->slotz[0]->fbmod;
        ch->slotz[1]->mod = &ch->slotz[0]->out;
      }
      else if (ch->con == 1) {
        ch->slotz[0]->mod = &ch->slotz[0]->fbmod;
        ch->slotz[1]->mod = &ch->chip->zeromod;
      }
    }
  }
  else {
    if (ch->con == 0) {
      ch->slotz[0]->mod = &ch->slotz[0]->fbmod;
      ch->slotz[1]->mod = &ch->slotz[0]->out;
    }
    else if (ch->con == 1) {
      ch->slotz[0]->mod = &ch->slotz[0]->fbmod;
      ch->slotz[1]->mod = &ch->chip->zeromod;
    }
  }
}