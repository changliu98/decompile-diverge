static int type_family(int type) {
  if (type == 0) return 241;
  if (type == 32 || type == 33 || type == 64 || type == 65) return 242;
  if (type == 96 || type == 97) return 242;
  if (type == 98) return 243;
  if (type == 128 || type == 129) return 242;
  if (type == 130) return 243;
  if (type == 131) return 244;
  if (type == 160) return 244;
  if (type >= 161 && type <= 164) return 244;
  if (type == 166 || type == 167) return 243;
  if (type == 192) return 245;
  if (type >= 224 && type <= 226) return 247;
  if (type >= 45057 && type <= 45060) return 244;
  if (type >= 53249 && type <= 53252) return 245;
  if (type == 524385) return 246;
  return 0;
}