static int
RDPDR_Drives_List_Send_Request(STREAM s, DRIVES_LIST_REQ *req)
{
 size_t domain_len = 0, username_len = 0;
 int success;

 if (!Stream_EnsureRemainingCapacity(s, 576))
 {
  do { } while (0);
  success = 0;
 }
 else
 {
  uint16 type;
  uint32 flags;

  type = 0x0001;
  flags = 0x00000012;

  Stream_Write_UINT16(s, type);
  Stream_Write_UINT32(s, flags);
  Stream_Write_UINT32(s, req->device_id);

  domain_len = strnlen(req->domain_name, 256);
  if (domain_len >= ((uint32) 1 << 31))
  {
   do { } while (0);
   success = 0;
  }
  else
  {
   Stream_Write_UINT32(s, (domain_len + 1) * sizeof(uint16));
   username_len = strnlen(req->username, 256);
   if (username_len >= ((uint32) 1 << 31))
   {
    do { } while (0);
    success = 0;
   }
   else
   {
    Stream_Write_UINT32(s, (username_len + 1) * sizeof(uint16));

    Stream_Seek(s, 558);

    if (Stream_Write_UTF16_String_From_UTF8(s, domain_len + 1, req->domain_name, domain_len, 1) < 0)
    {
     do { } while (0);
     success = 0;
    }
    else if (Stream_Write_UTF16_String_From_UTF8(s, username_len + 1, req->username, username_len, 1) < 0)
    {
     do { } while (0);
     success = 0;
    }
    else
    {
     success = 1;
    }
   }
  }
 }

 return success;
}