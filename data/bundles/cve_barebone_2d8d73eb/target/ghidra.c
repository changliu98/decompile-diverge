void EveAddVerdict(SCJsonBuilder *jb,Packet *p)

{
  uint8_t uVar1;
  _Bool _Var2;
  int iVar3;
  Packet *p_local;
  SCJsonBuilder *jb_local;
  
  SCJbOpenObject(jb,"verdict");
  _Var2 = PacketCheckAction(p,'\x1c');
  if (!_Var2) {
    _Var2 = PacketCheckAction(p,'\x02');
    if ((_Var2) && (iVar3 = EngineModeIsIPS(), iVar3 != 0)) {
      SCJbSetFormatted(jb,"\"action\":\"drop\"");
    }
    else {
      _Var2 = PacketCheckAction(p,0x80);
      if (_Var2) {
        SCJbSetFormatted(jb,"\"action\":\"accept\"");
      }
      else if (((p->alerts).alerts[(p->alerts).cnt].action & 0x20) == 0) {
        SCJbSetFormatted(jb,"\"action\":\"alert\"");
      }
      else {
        SCJbSetFormatted(jb,"\"action\":\"pass\"");
      }
    }
    goto LAB_0010156a;
  }
  iVar3 = EngineModeIsIPS();
  if (iVar3 == 0) {
    SCJbSetFormatted(jb,"\"action\":\"alert\"");
  }
  else {
    SCJbSetFormatted(jb,"\"action\":\"drop\"");
  }
  _Var2 = PacketCheckAction(p,'\x04');
  if (_Var2) {
    SCJbSetFormatted(jb,"\"reject-target\":\"to_client\"");
  }
  else {
    _Var2 = PacketCheckAction(p,'\b');
    if (_Var2) {
      SCJbSetFormatted(jb,"\"reject-target\":\"to_server\"");
    }
    else {
      _Var2 = PacketCheckAction(p,'\x10');
      if (_Var2) {
        SCJbSetFormatted(jb,"\"reject-target\":\"both\"");
      }
    }
  }
  SCJbOpenArray(jb,"reject");
  uVar1 = p->proto;
  if (uVar1 == '\x01') {
LAB_0010146e:
    SCJbAppendString(jb,"icmp-prohib");
  }
  else if (uVar1 == '\x06') {
    SCJbAppendString(jb,"tcp-reset");
  }
  else if ((uVar1 == '\x11') || (uVar1 == ':')) goto LAB_0010146e;
  SCJbClose(jb);
LAB_0010156a:
  SCJbClose(jb);
  return;
}