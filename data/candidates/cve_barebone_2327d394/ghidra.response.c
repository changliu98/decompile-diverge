/* WARNING: Removing unreachable block (ram,0x00101cac) */
/* WARNING: Removing unreachable block (ram,0x00101c36) */

UINT ainput_send_input_event(AInputClientContext *context,UINT64 flags,INT32 x,INT32 y)

{
  void *pvVar1;
  long lVar2;
  code *pcVar3;
  undefined8 uVar4;
  wStream *_s;
  ULONGLONG _v;
  char *pcVar5;
  size_t sVar6;
  BYTE *pBVar7;
  char ebuffer [128];
  wStream *s;
  wStream sbuffer;
  UINT64 time;
  BYTE buffer [32];
  GENERIC_CHANNEL_CALLBACK *callback;
  AINPUT_PLUGIN *ainput;
  INT32 y_local;
  INT32 x_local;
  UINT64 flags_local;
  AInputClientContext *context_local;
  UINT local_c;
  
  memset(buffer,0,0x20);
  memset(&sbuffer,0,0x38);
  _s = Stream_StaticInit(&sbuffer,buffer,0x20);
  if (_s == (wStream *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("s","/work/harness.c",0x208,
                  "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
  }
  if (context == (AInputClientContext *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("context","/work/harness.c",0x209,
                  "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
  }
  _v = winpr_GetTickCount64();
  pvVar1 = context->handle;
  if (pvVar1 == (void *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("ainput","/work/harness.c",0x20d,
                  "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
  }
  if (*(int *)((long)pvVar1 + 0x80) == 1) {
    lVar2 = *(long *)(*(long *)((long)pvVar1 + 0x38) + 0x28);
    if (lVar2 == 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("callback","/work/harness.c",0x216,
                    "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
    }
    memset(ebuffer,0,0x80);
    pcVar5 = ainput_flags_to_string(flags,ebuffer,0x80);
    vb_wlog_stub("channels.ainput.client","sending timestamp=0x%08lx, flags=%s, %dx%d",_v,pcVar5,
                 (ulong)(uint)x,(ulong)(uint)y);
    Stream_Write_UINT16_unchecked(_s,2);
    Stream_Write_UINT64(_s,_v);
    Stream_Write_UINT64(_s,flags);
    if (x < -0x80000000) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("(x) >= (-2147483647-1)","/work/harness.c",0x224,
                    "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
    }
    Stream_Write_INT32_unchecked(_s,x);
    if (y < -0x80000000) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("(y) >= (-2147483647-1)","/work/harness.c",0x225,
                    "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
    }
    Stream_Write_INT32_unchecked(_s,y);
    Stream_SealLength(_s);
    if (*(long *)(lVar2 + 0x30) == 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("callback->channel","/work/harness.c",0x229,
                    "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
    }
    if (**(long **)(lVar2 + 0x30) == 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("callback->channel->Write","/work/harness.c",0x22a,
                    "UINT ainput_send_input_event(AInputClientContext *, UINT64, INT32, INT32)");
    }
    pcVar3 = (code *)**(undefined8 **)(lVar2 + 0x30);
    uVar4 = *(undefined8 *)(lVar2 + 0x30);
    sVar6 = Stream_Length(_s);
    pBVar7 = Stream_Buffer(_s);
    local_c = (*pcVar3)(uVar4,sVar6 & 0xffffffff,pBVar7,0);
  }
  else {
    vb_wlog_stub("channels.ainput.client","Unsupported channel version %u.%u, aborting.",
                 (ulong)*(uint *)((long)pvVar1 + 0x80),(ulong)*(uint *)((long)pvVar1 + 0x84));
    local_c = 0x13;
  }
  return local_c;
}