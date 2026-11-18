void SetSubType(Header *header, byte subType)
{
 header->type_subType_PDU = (header->type_subType_PDU & 0xF0) | subType;
}