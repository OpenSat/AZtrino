/*
 * $Id: zapit.h,v 1.68 2004/10/27 16:08:40 lucgas Exp $
 */

#ifndef __zapit_h__
#define __zapit_h__

#include "client/zapitclient.h"

#include "bouquets.h"


void save_settings (bool write);
void getBlindFreqsAVL2108 (int scan_mode,int init_blind,char* startFreq,char* endFreq,char* pol,char* tone, std::list<TP_params> &listTP);
void getBlindFreqsSTV090x (int startfreq, int endfreq, int symrate,
	int step, unsigned int scan_v, unsigned int scan_h, int lof,
	unsigned int interactive, int fec, unsigned int adapter,
	unsigned int verbose, int delsys,
	unsigned int monitor, unsigned int polarity, int retune,
	unsigned int monitor_retune, int tone, std::list<TP_params> &listTP);

void *start_scanblindthread(void *);
void *start_scanthread(void *);
int start_scan(bool scan_mode);

/**************************************************************/
/*  functions for new command handling via CZapitClient       */
/*  these functions should be encapsulated in a class CZapit  */
/**************************************************************/

void addChannelToBouquet (const unsigned int bouquet, const t_channel_id channel_id);
void sendBouquets        (int connfd, const bool emptyBouquetsToo, CZapitClient::channelsMode mode = CZapitClient::MODE_CURRENT);
void internalSendChannels(int connfd, ZapitChannelList* channels, bool nonames);
void sendBouquetChannels (int connfd, const unsigned int bouquet, CZapitClient::channelsMode mode = CZapitClient::MODE_CURRENT, bool nonames = false);
void sendChannels        (int connfd, const CZapitClient::channelsMode mode = CZapitClient::MODE_CURRENT, const CZapitClient::channelsOrder order = CZapitClient::SORT_BOUQUET);
int startPlayBack(CZapitChannel *);
int stopPlayBack(bool stopemu);
unsigned int zapTo(const unsigned int channel);
unsigned int zapTo(const unsigned int bouquet, const unsigned int channel);
unsigned int zapTo_ChannelID(const t_channel_id channel_id, const bool isSubService);
void sendAPIDs(int connfd);
void enterStandby(void);
void leaveStandby(void);
void setVideoSystem_t(int video_system);

#define PAL	0
#define NTSC	1

#endif /* __zapit_h__ */
