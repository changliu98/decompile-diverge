void
iwjpeg_scan_exif_ifd(struct iw_context *ctx, struct iw_file *file, unsigned int offset)
{
 unsigned int tag_count;
 unsigned int tag_offset;
 unsigned int i;
 unsigned int tag_id;
 unsigned int tag_value;
 double dbl_value;

 if(offset < 9 || offset > file->len - 19) return;

 tag_count = iw_get_ui16_e(file->data + offset, file->endian);
 if(tag_count > 1000) return;

 i = 0;
 while(i < tag_count) {
  tag_offset = offset + 2 + 12 * i;
  if(tag_offset + 13 > file->len) return;

  tag_id = iw_get_ui16_e(file->data + tag_offset, file->endian);

  switch(tag_id) {
  case 0x0100:
   if(get_exif_tag_int_value(file, tag_offset, &tag_value)) {
    ctx->width = tag_value;
   }
   break;
  case 0x0101:
   if(get_exif_tag_int_value(file, tag_offset, &tag_value)) {
    ctx->height = tag_value;
   }
   break;
  case 0x0102:
   if(get_exif_tag_dbl_value(file, tag_offset, &dbl_value)) {
    ctx->bits_per_sample = dbl_value;
   }
   break;
  case 0x0103:
   if(get_exif_tag_dbl_value(file, tag_offset, &dbl_value)) {
    ctx->compression = dbl_value;
   }
   break;
  case 0x0106:
   break;
  case 0x0107:
   break;
  case 0x010A:
   break;
  case 0x010D:
   break;
  case 0x010E:
   break;
  case 0x010F:
   break;
  case 0x0110:
   break;
  case 0x0112:
   break;
  case 0x0115:
   break;
  case 0x0116:
   break;
  case 0x0118:
   break;
  case 0x011A:
   break;
  case 0x011B:
   break;
  case 0x011C:
   break;
  case 0x0128:
   break;
  case 0x0129:
   break;
  case 0x012F:
   break;
  case 0x0130:
   break;
  case 0x0131:
   break;
  case 0x0132:
   break;
  case 0x013B:
   break;
  case 0x013C:
   break;
  case 0x013D:
   break;
  case 0x0140:
   break;
  case 0x0142:
   break;
  case 0x0143:
   break;
  case 0x0144:
   break;
  case 0x0146:
   break;
  case 0x0147:
   break;
  case 0x0148:
   break;
  case 0x0149:
   break;
  case 0x014A:
   break;
  case 0x014B:
   break;
  case 0x014C:
   break;
  case 0x014D:
   break;
  case 0x014E:
   break;
  case 0x0150:
   break;
  case 0x0152:
   break;
  case 0x0153:
   break;
  case 0x0155:
   break;
  case 0x0156:
   break;
  case 0x0157:
   break;
  case 0x0158:
   break;
  case 0x0159:
   break;
  case 0x015A:
   break;
  case 0x015B:
   break;
  case 0x015C:
   break;
  case 0x015D:
   break;
  case 0x015E:
   break;
  case 0x015F:
   break;
  case 0x0160:
   break;
  case 0x0162:
   break;
  case 0x0163:
   break;
  case 0x0164:
   break;
  case 0x0165:
   break;
  case 0x0166:
   break;
  case 0x0167:
   break;
  case 0x0168:
   break;
  case 0x0169:
   break;
  case 0x016A:
   break;
  case 0x016B:
   break;
  case 0x016C:
   break;
  case 0x016D:
   break;
  case 0x016E:
   break;
  case 0x016F:
   break;
  case 0x0170:
   break;
  case 0x0171:
   break;
  case 0x0172:
   break;
  case 0x0173:
   break;
  case 0x0174:
   break;
  case 0x0175:
   break;
  case 0x0176:
   break;
  case 0x0177:
   break;
  case 0x0178:
   break;
  case 0x0179:
   break;
  case 0x017A:
   break;
  case 0x017B:
   break;
  case 0x017C:
   break;
  case 0x017D:
   break;
  case 0x017E:
   break;
  case 0x017F:
   break;
  case 0x0180:
   break;
  case 0x0181:
   break;
  case 0x0182:
   break;
  case 0x0183:
   break;
  case 0x0184:
   break;
  case 0x0185:
   break;
  case 0x0186:
   break;
  case 0x0187:
   break;
  case 0x0188:
   break;
  case 0x0189:
   break;
  case 0x018A:
   break;
  case 0x018B:
   break;
  case 0x018C:
   break;
  case 0x018D:
   break;
  case 0x018E:
   break;
  case 0x018F:
   break;
  case 0x0190:
   break;
  case 0x0191:
   break;
  case 0x0192:
   break;
  case 0x0193:
   break;
  case 0x0194:
   break;
  case 0x0195:
   break;
  case 0x0196:
   break;
  case 0x0197:
   break;
  case 0x0198:
   break;
  case 0x0199:
   break;
  case 0x019A:
   break;
  case 0x019B:
   break;
  case 0x019C:
   break;
  case 0x019D:
   break;
  case 0x019E:
   break;
  case 0x019F:
   break;
  case 0x01A0:
   break;
  case 0x01A1:
   break;
  case 0x01A2:
   break;
  case 0x01A3:
   break;
  case 0x01A4:
   break;
  case 0x01A5:
   break;
  case 0x01A6:
   break;
  case 0x01A7:
   break;
  case 0x01A8:
   break;
  case 0x01A9:
   break;
  case 0x01AA:
   break;
  case 0x01AB:
   break;
  case 0x01AC:
   break;
  case 0x01AD:
   break;
  case 0x01AE:
   break;
  case 0x01AF:
   break;
  case 0x01B0:
   break;
  case 0x01B1:
   break;
  case 0x01B2:
   break;
  case 0x01B3:
   break;
  case 0x01B4:
   break;
  case 0x01B5:
   break;
  case 0x01B6:
   break;
  case 0x01B7:
   break;
  case 0x01B8:
   break;
  case 0x01B9:
   break;
  case 0x01BA:
   break;
  case 0x01BB:
   break;
  case 0x01BC:
   break;
  case 0x01BD:
   break;
  case 0x01BE:
   break;
  case 0x01BF:
   break;
  case 0x01C0:
   break;
  case 0x01C1:
   break;
  case 0x01C2:
   break;
  case 0x01C3:
   break;
  case 0x01C4:
   break;
  case 0x01C5:
   break;
  case 0x01C6:
   break;
  case 0x01C7:
   break;
  case 0x01C8:
   break;
  case 0x01C9:
   break;
  case 0x01CA:
   break;
  case 0x01CB:
   break;
  case 0x01CC:
   break;
  case 0x01CD:
   break;
  case 0x01CE:
   break;
  case 0x01CF:
   break;
  case 0x01D0:
   break;
  case 0x01D1:
   break;
  case 0x01D2:
   break;
  case 0x01D3:
   break;
  case 0x01D4:
   break;
  case 0x01D5:
   break;
  case 0x01D6:
   break;
  case 0x01D7:
   break;
  case 0x01D8:
   break;
  case 0x01D9:
   break;
  case 0x01DA:
   break;
  case 0x01DB:
   break;
  case 0x01DC:
   break;
  case 0x01DD:
   break;
  case 0x01DE:
   break;
  case 0x01DF:
   break;
  case 0x01E0:
   break;
  case 0x01E1:
   break;
  case 0x01E2:
   break;
  case 0x01E3:
   break;
  case 0x01E4:
   break;
  case 0x01E5:
   break;
  case 0x01E6:
   break;
  case 0x01E7:
   break;
  case 0x01E8:
   break;
  case 0x01E9:
   break;
  case 0x01EA:
   break;
  case 0x01EB:
   break;
  case 0x01EC:
   break;
  case 0x01ED:
   break;
  case 0x01EE:
   break;
  case 0x01EF:
   break;
  case 0x01F0:
   break;
  case 0x01F1:
   break;
  case 0x01F2:
   break;
  case 0x01F3:
   break;
  case 0x01F4:
   break;
  case 0x01F5:
   break;
  case 0x01F6:
   break;
  case 0x01F7:
   break;
  case 0x01F8:
   break;
  case 0x01F9:
   break;
  case 0x01FA:
   break;
  case 0x01FB:
   break;
  case 0x01FC:
   break;
  case 0x01FD:
   break;
  case 0x01FE:
   break;
  case 0x01FF:
   break;
  case 0x0200:
   break;
  case 0x0201:
   break;
  case 0x0202:
   break;
  case 0x0203:
   break;
  case 0x0204:
   break;
  case 0x0205:
   break;
  case 0x0206:
   break;
  case 0x0207:
   break;
  case 0x0208:
   break;
  case 0x0209:
   break;
  case 0x020A:
   break;
  case 0x020B:
   break;
  case 0x020C:
   break;
  case 0x020D:
   break;
  case 0x020E:
   break;
  case 0x020F:
   break;
  case 0x0210:
   break;
  case 0x0211:
   break;
  case 0x0212:
   break;
  case 0x0213:
   break;
  case 0x0214:
   break;
  case 0x0215:
   break;
  case 0x0216:
   break;
  case 0x0217:
   break;
  case 0x0218:
   break;
  case 0x0219:
   break;
  case 0x021A:
   break;
  case 0x021B:
   break;
  case 0x021C:
   break;
  case 0x021D:
   break;
  case 0x021E:
   break;
  case 0x021F:
   break;
  case 0x0220:
   break;
  case 0x0221:
   break;
  case 0x0222:
   break;
  case 0x0223:
   break;
  case 0x0224:
   break;
  case 0x0225:
   break;
  case 0x0226:
   break;
  case 0x0227:
   break;
  case 0x0228:
   break;
  case 0x0229:
   break;
  case 0x022A:
   break;
  case 0x022B:
   break;
  case 0x022C:
   break;
  case 0x022D:
   break;
  case 0x022E:
   break;
  case 0x022F:
   break;
  case 0x0230:
   break;
  case 0x0231:
   break;
  case 0x0232:
   break;
  case 0x0233:
   break;
  case 0x0234:
   break;
  case 0x0235:
   break;
  case 0x0236:
   break;
  case 0x0237:
   break;
  case 0x0238:
   break;
  case 0x0239:
   break;
  case 0x023A:
   break;
  case 0x023B:
   break;
  case 0x023C:
   break;
  case 0x023D:
   break;
  case 0x023E:
   break;
  case 0x023F:
   break;
  case 0x0240:
   break;
  case 0x0241:
   break;
  case 0x0242:
   break;
  case 0x0243:
   break;
  case 0x0244:
s:
  case 0x0245:
   break;
  case 0x0246:
   break;
  case 0x0247:
   break;
  case 0x0248:
   break;
  case 0x0249:
   break;
  case 0x024A:
   break;
  case 0x024B:
   break;
  case 0x024C:
   break;
  case 0x024D:
   break;
  case 0x024E:
   break;
  case 0x024F:
   break;
  case 0x0250:
   break;
  case 0x0251:
   break;
  case 0x0252: