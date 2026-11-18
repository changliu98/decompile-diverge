void __cdecl OPL2_ChannelSetupCon(opl2_channel *channel)
{
  // The logic for 'con' and the fallback is identical regardless of 'chtype'.
  // We can pull this shared logic out to avoid redundant code paths.
  if (channel->chtype == 1 && (channel->ch_num == 7 || channel->ch_num == 8))
  {
    channel->slotz[0]->mod = &channel->chip->zeromod;
    channel->slotz[1]->mod = &channel->chip->zeromod;
  }
  else if (channel->con)
  {
    // Based on the decompiled logic, 'con' is effectively a boolean flag.
    // The only checked value is 1, which behaves identically to the truthy condition.
    channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
    channel->slotz[1]->mod = &channel->chip->zeromod;
  }
  else
  {
    channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
    channel->slotz[1]->mod = &channel->slotz[0]->out;
  }
}