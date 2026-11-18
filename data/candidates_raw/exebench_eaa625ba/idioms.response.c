int utf8_to_utf32(unsigned int *utf32, char *utf8)
{
  unsigned int u = (uint32_t)(unsigned char)(utf8[0]);
  if (u < 0x80)
  {
    *utf32 = (unsigned int)u;
    return (u == 0) ? 0 : 1;
  }
  else if (u < 0xc0)
  {
    *utf32 = (unsigned int)-1;
    return -1;
  }
  else if (u < 0xe0)
  {
    unsigned int u1 = (uint32_t)(unsigned char)(utf8[1]);
    if (u1 < 0x80 || u1 > 0xbf)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else if (u < 0xe0 || (u & 0xe) != 0)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else
    {
      *utf32 = (u & 0x1f) << 6 | (u1 & 0x3f);
      return 2;
    }
  }
  else if (u < 0xf0)
  {
    unsigned int u1 = (uint32_t)(unsigned char)(utf8[1]);
    if (u1 < 0x80 || u1 > 0xbf)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else if (u < 0xf0 || (u & 0xe) != 0)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else
    {
      unsigned int u2 = (uint32_t)(unsigned char)(utf8[2]);
      if (u2 < 0x80 || u2 > 0xbf)
      {
        *utf32 = (unsigned int)-1;
        return -1;
      }
      else if (u < 0xf8 || (u & 0xc) != 0)
      {
        *utf32 = (unsigned int)-1;
        return -1;
      }
      else
      {
        *utf32 = (u & 0xf) << 12 | (u1 & 0x3f) << 6 | (u2 & 0x3f);
        return 3;
      }
    }
  }
  else if (u < 0xf8)
  {
    unsigned int u1 = (uint32_t)(unsigned char)(utf8[1]);
    if (u1 < 0x80 || u1 > 0xbf)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else if (u < 0xf8 || (u & 0xe) != 0)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else
    {
      unsigned int u2 = (uint32_t)(unsigned char)(utf8[2]);
      if (u2 < 0x80 || u2 > 0xbf)
      {
        *utf32 = (unsigned int)-1;
        return -1;
      }
      else if (u < 0xfc || (u & 0xc) != 0)
      {
        *utf32 = (unsigned int)-1;
        return -1;
      }
      else
      {
        unsigned int u3 = (uint32_t)(unsigned char)(utf8[3]);
        if (u3 < 0x80 || u3 > 0xbf)
        {
          *utf32 = (unsigned int)-1;
          return -1;
        }
        else if (u < 0xfe || (u & 0xa) != 0)
        {
          *utf32 = (unsigned int)-1;
          return -1;
        }
        else
        {
          *utf32 = (u & 0xf) << 18 | (u1 & 0x3f) << 12 | (u2 & 0x3f) << 6 | (u3 & 0x3f);
          return 4;
        }
      }
    }
  }
  else if (u < 0xfc)
  {
    unsigned int u1 = (uint32_t)(unsigned char)(utf8[1]);
    if (u1 < 0x80 || u1 > 0xbf)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else if (u < 0xfc || (u & 0xe) != 0)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else
    {
      unsigned int u2 = (uint32_t)(unsigned char)(utf8[2]);
      if (u2 < 0x80 || u2 > 0xbf)
      {
        *utf32 = (unsigned int)-1;
        return -1;
      }
      else if (u < 0xfe || (u & 0xc) != 0)
      {
        *utf32 = (unsigned int)-1;
        return -1;
      }
      else
      {
        unsigned int u3 = (uint32_t)(unsigned char)(utf8[3]);
        if (u3 < 0x80 || u3 > 0xbf)
        {
          *utf32 = (unsigned int)-1;
          return -1;
        }
        else
        {
          *utf32 = (u & 0xf) << 24 | (u1 & 0x3f) << 18 | (u2 & 0x3f) << 12 | (u3 & 0x3f) << 6;
          return 5;
        }
      }
    }
  }
  else if (u < 0xfe)
  {
    unsigned int u1 = (uint32_t)(unsigned char)(utf8[1]);
    if (u1 < 0x80 || u1 > 0xbf)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else if (u < 0xfe || (u & 0xe) != 0)
    {
      *utf32 = (unsigned int)-1;
      return -1;
    }
    else
    {
      unsigned int u2 = (uint32_t)(unsigned char)(utf8[2]);
      if (u2 < 0x80 || u2 > 0xbf)
      {
        *utf32 = (unsigned int)-1;
        return -1;
      }
      else
      {
        *utf32 = (u & 0xf) << 30 | (u1 & 0x3f) << 24 | (u2 & 0x3f) << 18;
        return 6;
      }
    }
  }
  else
  {
    *utf32 = (unsigned int)-1;
    return -1;
  }
}