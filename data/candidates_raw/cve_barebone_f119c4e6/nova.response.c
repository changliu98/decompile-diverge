int func0(struct params *p, struct ieee80211_frame *wh, int len)
{
	int rc = 0;
	unsigned short *ptr;
	unsigned char *bssid, *da, *sa;
	unsigned char *buf;
	unsigned char *ssid;
	unsigned int seq;
	int ssidlen;
	struct ieee80211_frame *wh2;
	struct ieee80211_frame *wh3;
	struct ieee80211_frame *wh4;
	struct ieee80211_frame *wh5;

	bssid = NULL;
	da = NULL;
	sa = NULL;
	buf = NULL;
	ssid = NULL;
	seq = 0;
	ssidlen = 0;
	ptr = NULL;

	while (1) {
		wh2 = wh3 = wh4 = wh5 = NULL;
		wh2 = (struct ieee80211_frame*) malloc(sizeof(struct ieee80211_frame));
		if (!wh2) {
			printf("malloc failed %d %d %d %d %d\n", 
				sizeof(struct ieee80211_frame),
				sizeof(struct ieee80211_frame),
				sizeof(struct ieee80211_frame),
				sizeof(struct ieee80211_frame),
				sizeof(struct ieee80211_frame));
			rc = -1;
			break;
		}

		rc = read_packet(p, wh2, len);
		if (rc < 1) {
			rc = -1;
			break;
		}

		bssid = wh2->i_addr2;
		da = wh2->i_addr1;
		sa = wh2->i_addr3;
		ssid = wh2->i_payload;
		ssidlen = wh2-