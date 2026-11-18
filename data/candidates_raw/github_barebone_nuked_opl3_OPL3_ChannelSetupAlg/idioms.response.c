void opl3_set_channel(struct opl3_channel *channel)
{
  if (channel->chtype == 3)
  {
    if (channel->ch_num == 7 || channel->ch_num == 8)
    {
      channel->slotz[0]->mod = &channel->chip->zeromod;
      channel->slotz[1]->mod = &channel->chip->zeromod;
    }
    else
    {
      if (channel->alg & 1)
      {
        if (channel->alg & 1)
        {
          channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
          channel->slotz[1]->mod = &channel->chip->zeromod;
        }
      }
      else
      {
        channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
        channel->slotz[1]->mod = &channel->slotz[0]->out;
      }
    }
  }
  else
  {
    if (channel->alg & 8)
    {
      return;
    }
    if (channel->alg & 4)
    {
      channel->pair->out[0] = &channel->chip->zeromod;
      channel->pair->out[1] = &channel->chip->zeromod;
      channel->pair->out[2] = &channel->chip->zeromod;
      channel->pair->out[3] = &channel->chip->zeromod;
      switch (channel->alg & 3)
      {
        case 0:
          channel->pair->slotz[0]->mod = &channel->pair->slotz[0]->fbmod;
          channel->pair->slotz[1]->mod = &channel->pair->slotz[0]->out;
          channel->slotz[0]->mod = &channel->pair->slotz[1]->out;
          channel->slotz[1]->mod = &channel->slotz[0]->out;
          channel->out[0] = &channel->slotz[1]->out;
          channel->out[1] = &channel->chip->zeromod;
          channel->out[2] = &channel->chip->zeromod;
          channel->out[3] = &channel->chip->zeromod;
          break;
        case 1:
          channel->pair->slotz[0]->mod = &channel->pair->slotz[0]->fbmod;
          channel->pair->slotz[1]->mod = &channel->pair->slotz[0]->out;
          channel->slotz[0]->mod = &channel->chip->zeromod;
          channel->slotz[1]->mod = &channel->slotz[0]->out;
          channel->out[0] = &channel->pair->slotz[1]->out;
          channel->out[1] = &channel->slotz[1]->out;
          channel->out[2] = &channel->chip->zeromod;
          channel->out[3] = &channel->chip->zeromod;
          break;
        case 2:
          channel->pair->slotz[0]->mod = &channel->pair->slotz[0]->fbmod;
          channel->pair->slotz[1]->mod = &channel->chip->zeromod;
          channel->slotz[0]->mod = &channel->pair->slotz[1]->out;
          channel->slotz[1]->mod = &channel->slotz[0]->out;
          channel->out[0] = &channel->pair->slotz[0]->out;
          channel->out[1] = &channel->slotz[1]->out;
          channel->out[2] = &channel->chip->zeromod;
          channel->out[3] = &channel->chip->zeromod;
          break;
        case 3:
          channel->pair->slotz[0]->mod = &channel->pair->slotz[0]->fbmod;
          channel->pair->slotz[1]->mod = &channel->chip->zeromod;
          channel->slotz[0]->mod = &channel->pair->slotz[1]->out;
          channel->slotz[1]->mod = &channel->chip->zeromod;
          channel->out[0] = &channel->pair->slotz[0]->out;
          channel->out[1] = &channel->slotz[0]->out;
          channel->out[2] = &channel->slotz[1]->out;
          channel->out[3] = &channel->chip->zeromod;
          break;
      }
    }
    else
    {
      if (channel->alg & 1)
      {
        if (channel->alg & 1)
        {
          channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
          channel->slotz[1]->mod = &channel->chip->zeromod;
          channel->out[0] = &channel->slotz[0]->out;
          channel->out[1] = &channel->slotz[1]->out;
          channel->out[2] = &channel->chip->zeromod;
          channel->out[3] = &channel->chip->zeromod;
        }
      }
      else
      {
        channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
        channel->slotz[1]->mod = &channel->slotz[0]->out;
        channel->out[0] = &channel->slotz[1]->out;
        channel->out[1] = &channel->chip->zeromod;
        channel->out[2] = &channel->chip->zeromod;
        channel->out[3] = &channel->chip->zeromod;
      }
    }
  }
}