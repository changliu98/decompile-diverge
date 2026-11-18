int func0(WORD wChannels, WORD wBlockSize, WORD wBitsPerSample) {
 int n = (wBlockSize + wChannels) * (2*wBitsPerSample);
 return n;
}