void OPL3_ChannelSetupAlg( struct h264_decoder* dec_params )
{
 int i;
 if ((dec_params->PicType & 3) == 3)
 {
  if ((dec_params->field_pic_flag == 7) || (dec_params->field_pic_flag == 8))
  {
   dec_params->top_field[3] = dec_params->top_field[0] + 45 * 128;
   dec_params->bottom_field[3] = dec_params->top_field[0] + 45 * 128;
   return;
  }
  else
  {
   int field1 = (dec_params->field_pic_flag & 1);
   if (field1)
   {
    while (--field1)
    {
     if (field1)
     {
      break;
     }
     else
     {
      dec_params->top_field[3] = dec_params->top_field[0] + 18;
      dec_params->bottom_field[3] = dec_params->top_field[0] + 16;
      return;
     }
    }
    dec_params->top_field[3] = dec_params->top_field[0] + 18;
    dec_params->bottom_field[3] = dec_params->top_field[0] + 45 * 128;
   }
   else
   {
    dec_params->top_field[3] = dec_params->top_field[0] + 18;
    dec_params->bottom_field[3] = dec_params->top_field[0] + 16;
   }
  }
 }
 else
 {
  if ((dec_params->field_pic_flag & 8) != 0)
  {
   return;
  }
  else
  {
   if ((dec_params->field_pic_flag & 4) != 0)
   {
    dec_params->top_field[4] = dec_params->top_field[0] + 45 * 128;
    dec_params->top_field[5] = dec_params->top_field[0] + 45 * 128;
    dec_params->top_field[6] = dec_params->top_field[0] + 45 * 128;
    dec_params->top_field[7] = dec_params->top_field[0] + 45 * 128;

    switch (dec_params->field_pic_flag & 3)
    {
    case 0:
     dec_params->top_field[0] += 18;
     dec_params->bottom_field[0] += 16;
     dec_params->top_field[3] = dec_params->top_field[1] + 16;
     dec_params->bottom_field[3] = dec_params->top_field[0] + 16;
     dec_params->top_field[4] = dec_params->bottom_field[0] + 16;
     dec_params->top_field[5] = dec_params->top_field[0] + 45 * 128;
     dec_params->top_field[6] = dec_params->top_field[0] + 45 * 128;
     dec_params->top_field[7] = dec_params->top_field[0] + 45 * 128;
     break;
    case 1:
     dec_params->top_field[0] += 18;
     dec_params->bottom_field[0] += 16;
     dec_params->top_field[3] = dec_params->top_field[0] + 45 * 128;
     dec_params->bottom_field[3] = dec_params->top_field[0] + 16;
     dec_params->top_field[4] = dec_params->bottom_field[0] + 16;
     dec_params->top_field[5] = decparams->bottom_field[0] + 16;
     decparams->top_field[6] = dec_params->top_field[0] + 45 * 128;
     decparams->top_field[7] = dec_params->top_field[0] + 45 * 128;
     break;
    case 2:
     dec_params->top_field[0] += 18;
     dec_params->bottom_field[0] = dec_params->top_field[0] + 45 * 128;
     dec_params->top_field[3] = decparams->bottom_field[0] + 16;
     decparams->bottom_field[3] = dec_params->top_field[0] + 16;
     decparams->top_field[4] = decparams->top_field[0] + 16;
     decparams->top_field[5] = decparams->bottom_field[0] + 16;
     decparams->top_field[6] = decparams->top_field[0] + 45 * 128;
     decparams->top_field[7] = decparams->top_field[0] + 45 * 128;
     break;
    case 3:
     dec_params->top_field[0] += 18;
     decparams->bottom_field[0] = decparams->top_field[0] + 45 * 128;
     decparams->top_field[3] = decparams->bottom_field[0] + 16;
     decparams->bottom_field[3] = decparams->top_field[0] + 45 * 128;
     decparams->top_field[4] = decparams->top_field[0] + 16;
     decparams->top_field[5] = decparams->top_field[0] + 16;
     decparams->top_field[6] = decparams->bottom_field[0] + 16;
     decparams->top_field[7] = decparams->top_field[0] + 45 * 128;
     break;
    }
   }
   else
   {
    int field1 = (dec_params->field_pic_flag & 1);
    if (field1)
    {
     while (--field1)
     {
      if (field1)
      {
       break;
      }
      else
      {
       dec_params->top_field[3] = dec_params->top_field[0] + 18;
       dec_params->bottom_field[3] = dec_params->top_field[0] + 16;
       dec_params->top_field[4] = dec_params->bottom_field[0] + 16;
       dec_params->top_field[5] = dec_params->top_field[0] + 45 * 128;
       dec_params->top_field[6] = dec_params->top_field[0] + 45 * 128;
       dec_params->top_field[7] = dec_params->top_field[0] + 45 * 128;
       return;
      }
     }
     dec_params->top_field[3] = dec_params->top_field[0] + 18;
     dec_params->bottom_field[3] = dec_params->top_field[0] + 45 * 128;
     dec_params->top_field[4] = dec_params->top_field[0] + 16;
     dec_params->bottom_field[4] = dec_params->bottom_field[0] + 16;
     dec_params->top_field[5] = dec_params->top_field[0] + 45 * 128;
     dec_params->top_field[7] = dec_params->top_field[0] + 45 * 128;
    }
    else
    {
     dec_params->top_field[3] = dec_params->top_field[0] + 18;
     dec_params->bottom_field[3] = dec_params->top_field[0] + 16;
     dec_params->top_field[4] = dec_params->bottom_field[0] + 16;
     dec_params->top_field[5] = dec_params->top_field[0] + 45 * 128;
     dec_params->top_field[6] = dec_params->top_field[0] + 45 * 128;
     dec_params->top_field[7] = dec_params->top_field[0] + 45 * 128;
    }
   }
  }
 }
}