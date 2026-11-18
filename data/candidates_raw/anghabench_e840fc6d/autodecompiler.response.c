static int base64_encode_value(char value_in)
{
 char encoded;
 switch (value_in) {
 case 63:
  encoded = '=';
  break;
 default:
  encoded = base64_encode_value.encoding[value_in];
 }
 return encoded;
}