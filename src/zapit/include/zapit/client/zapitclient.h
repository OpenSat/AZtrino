/*
  Client-Interface f�r zapit  -   DBoxII-Project

  License: GPL

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef __zapitclient__
#define __zapitclient__


#include <string>
#include <vector>
#include <list>


/* zapit */
#include "zapittypes.h"
#include <connection/basicclient.h>

#define CHANNEL_NAME_SIZE 40

class CZapitClient:public CBasicClient
{
 private:
	virtual const unsigned char   getVersion   () const;
	virtual const          char * getSocketName() const;

 public:
	enum events
		{
			FIRST_EVENT_MARKER,           // <- no actual event, needed by pzapit
			EVT_ZAP_COMPLETE = FIRST_EVENT_MARKER,
			EVT_ZAP_COMPLETE_IS_NVOD,
			EVT_ZAP_FAILED,
			EVT_ZAP_SUB_COMPLETE,
			EVT_ZAP_SUB_FAILED,
			EVT_ZAP_MOTOR,
			EVT_RECORDMODE_ACTIVATED,
			EVT_RECORDMODE_DEACTIVATED,
			EVT_SCAN_COMPLETE,
			EVT_SCAN_FAILED,
			EVT_SCAN_NUM_TRANSPONDERS,
			EVT_SCAN_REPORT_NUM_SCANNED_TRANSPONDERS,
 			EVT_SCAN_REPORT_FREQUENCY,
 			EVT_SCAN_REPORT_FREQUENCYP,
 			EVT_SCAN_SERVICENAME,
 			EVT_SCAN_FOUND_A_CHAN,
 			EVT_SCAN_FOUND_TV_CHAN,
 			EVT_SCAN_FOUND_RADIO_CHAN,
 			EVT_SCAN_FOUND_DATA_CHAN,
			EVT_SCAN_SATELLITE,
			EVT_SCAN_NUM_CHANNELS,
			EVT_SCAN_PROVIDER,
			EVT_BOUQUETS_CHANGED,
			EVT_ZAP_CA_CLEAR,
			EVT_ZAP_CA_LOCK,
			EVT_ZAP_CA_FTA,
			EVT_ZAP_CA_ID,
			EVT_SDT_CHANGED,
			EVT_SERVICES_CHANGED,
			LAST_EVENT_MARKER             // <- no actual event, needed by pzapit
		};

	enum zapStatus
		{
			ZAP_OK = 0x01,
			ZAP_IS_NVOD = 0x02,
			ZAP_INVALID_PARAM = 0x04
		};

	enum bouquetMode
		{
			BM_CREATEBOUQUETS,
			BM_DELETEBOUQUETS,
			BM_DONTTOUCHBOUQUETS,
			BM_UPDATEBOUQUETS,
			BM_CREATESATELLITEBOUQUET
		};

  	enum scanType
  		{
  			ST_TVRADIO,
  			ST_TV,
  			ST_RADIO,
  			ST_ALL
  		};

	typedef enum channelsMode_
		{
			MODE_CURRENT,
			MODE_TV,
			MODE_RADIO
		} channelsMode;

	typedef enum channelsOrder_
		{
			SORT_ALPHA,
			SORT_BOUQUET
		} channelsOrder;


	struct commandAddSubServices
	{
		t_original_network_id original_network_id;
		t_service_id          service_id;
		t_transport_stream_id transport_stream_id;
	};


	struct commandSetScanSatelliteList
	{
		char satName[50];
		int  position;
	};
	typedef std::vector<commandSetScanSatelliteList> ScanSatelliteList;

	struct commandSetScanMotorPosList
	{
		t_satellite_position satPosition;
		int motorPos;
	};
	typedef std::vector<commandSetScanMotorPosList> ScanMotorPosList;

	typedef std::vector<commandAddSubServices> subServiceList;

	struct responseGetLastChannel
	{
		unsigned int	channelNumber;
		char		mode;
	};

	struct responseGetBouquets
	{
		unsigned int bouquet_nr;
		char	 name[30];
		bool	 locked;
		bool	 hidden;
	};

	typedef std::vector<responseGetBouquets> BouquetList;

	struct responseChannels
	{
		unsigned int nr;
		t_channel_id channel_id;
		char	 name[CHANNEL_NAME_SIZE];
		t_satellite_position satellitePosition;
		unsigned char service_type;
	};

	struct responseGetBouquetChannels : public responseChannels
	{};

	typedef std::vector<responseGetBouquetChannels> BouquetChannelList;

	struct responseNChannels
	{
		unsigned int nr;
	};

	struct responseGetBouquetNChannels : public responseNChannels
	{};

	typedef std::vector<responseGetBouquetNChannels> BouquetNChannelList;

	struct responseGetAPIDs
	{
		uint32_t    pid;
		char    desc[25];
		int     is_ac3;
		int     component_tag;
	};

	typedef std::vector<responseGetAPIDs> APIDList;

	struct responseGetOtherPIDs
	{
		uint		vpid;
		uint		ecmpid;
		uint		vtxtpid;
		uint		pcrpid;
		uint		selected_apid;
		uint		pmtpid;
		uint		privatepid;
	};

	class CCurrentServiceInfo
		{
		public:
			t_original_network_id onid;
			t_service_id           sid;
			t_transport_stream_id tsid;
			unsigned short	vpid;
			unsigned short  vtype;
			unsigned short	apid;
			unsigned short	pcrpid;
			unsigned short	vtxtpid;
			unsigned int	tsfrequency;
			unsigned char	polarisation;
			unsigned char	diseqc;
			unsigned short  pmtpid;
			uint32_t	rate;
			fe_code_rate	fec;
		};

	struct responseGetPIDs
	{
		responseGetOtherPIDs	PIDs;
		APIDList		APIDs;
	};

	struct responseGetSatelliteList
	{
		char satName[50];
		t_satellite_position satPosition;
		uint8_t motorPosition;
		int satDiseqc;
	};
	typedef std::vector<responseGetSatelliteList> SatelliteList;


	struct responseFESignal
	{
		unsigned int  sig;
		unsigned int  snr;
		unsigned long ber;
		// maybe later... 
		// int          has_lock;
		// int          has_signal;
		// int          has_sync;
		// int          has_carrier;
	};




#define CI_FLAG_IQ_BIT                  0x00        /// bit 0
#define CI_FLAG_IQ_BIT_MASK             0x01        /// one bit
#define CI_FLAG_IQ_NO_SWAPPED           0x00		/// IQ is not swapped
#define CI_FLAG_IQ_SWAPPED              0x01		/// IQ is swapped

#define CI_FLAG_DVBS2_BIT                0x02		/// bit 4, 3, 2
#define CI_FLAG_DVBS2_BIT_MASK           0x1c		/// three bits
#define CI_FLAG_DVBS 	                 0x00		/// DVB-S standard
#define CI_FLAG_DVBS2                    0x01		/// DVB-S2 standard
#define CI_FLAG_DVBSDTV                  0x02		/// DirectTV DVBs
#define CI_FLAG_DVBSDTV_AMC              0x03		/// DirectTV DVBS2
#define CI_FLAG_DVBS2_UNDEF              0x04       /// Do not know the standard

#define CI_FLAG_IQ_AUTO_BIT				0x05		/// bit 5
#define CI_FLAG_IQ_AUTO_BIT_MASK		0x20        /// one bit
#define CI_FLAG_IQ_AUTO_BIT_OFF			0x00        /// Do not do auto swapp IQ and try again
#define CI_FLAG_IQ_AUTO_BIT_AUTO		0x01        /// Auto swapp IQ and try again

#define CI_FLAG_LOCK_MODE_BIT			0x06		/// bit 6 controls channel lock mode
#define CI_FLAG_LOCK_MODE_BIT_MASK		0x40		/// Lock mode bit mask


 public:
	/*****************************/
	/*                           */
	/* shutdown the zapit daemon */
	/*                           */
	/*****************************/
	void shutdown();


	/****************************************/
	/*					*/
	/* general functions for zapping	*/
	/*					*/
	/****************************************/

	/* zaps to channel of specified bouquet */
	/* bouquets are numbered starting at 0 */
	void zapTo(const unsigned int bouquet, const unsigned int channel);

	/* zaps to channel  */
	void zapTo(const unsigned int channel);

	/* zaps to channel, returns the "zap-status" */
	unsigned int zapTo_serviceID(const t_channel_id channel_id);

	/* zaps to subservice, returns the "zap-status" */
	unsigned int zapTo_subServiceID(const t_channel_id channel_id);

	/* zaps to channel, does NOT wait for completion (uses event) */
	void zapTo_serviceID_NOWAIT(const t_channel_id channel_id);

	/* zaps to subservice, does NOT wait for completion (uses event) */
	void zapTo_subServiceID_NOWAIT(const t_channel_id channel_id);

	/* return the current (tuned) ServiceID */
	t_channel_id getCurrentServiceID();

	/* return the current satellite position */
	int32_t getCurrentSatellitePosition();

	/* get last channel-information */
	void getLastChannel(unsigned int &channumber, char &mode);

	/* audiochan set */
	void setAudioChannel(const unsigned int channel);

	/* gets all bouquets */
	/* bouquets are numbered starting at 0 */
	void getBouquets( BouquetList& bouquets, const bool emptyBouquetsToo = false, const bool utf_encoded = false, channelsMode mode = MODE_CURRENT);

 private:
	bool receive_channel_list(BouquetChannelList& channels, const bool utf_encoded);
	bool receive_nchannel_list(BouquetNChannelList& channels);

 public:
	/* gets all channels that are in specified bouquet */
	/* bouquets are numbered starting at 0 */
	bool getBouquetChannels(const unsigned int bouquet, BouquetChannelList& channels, const channelsMode mode = MODE_CURRENT, const bool utf_encoded = false);
	bool getBouquetNChannels(const unsigned int bouquet, BouquetNChannelList& channels, const channelsMode mode = MODE_CURRENT, const bool utf_encoded = false);

	/* gets all channels */
	bool getChannels(BouquetChannelList& channels, const channelsMode mode = MODE_CURRENT, const channelsOrder order = SORT_BOUQUET, const bool utf_encoded = false);


	/* request information about a particular channel_id */

	/* channel name */
	std::string getChannelName(const t_channel_id channel_id);

	/* is channel a TV channel ? */
	bool isChannelTVChannel(const t_channel_id channel_id);


	/* get the current_TP */
	bool get_current_TP(TP_params* TP);

	/* restore bouquets so as if they where just loaded*/
	void restoreBouquets();

	/* reloads channels and services*/
	void reinitChannels();

  	/* called when sectionsd updates currentservices.xml */
  	void reloadCurrentServices();

	/* get current APID-List */
	void getPIDS( responseGetPIDs& pids );

	/* get info about the current serivice */
	CZapitClient::CCurrentServiceInfo getCurrentServiceInfo();

	/* transfer SubService-List to zapit */
	void setSubServices( subServiceList& subServices );

	/* set Mode */
	void setMode(const channelsMode mode);

	/* set Mode */
	int getMode();

	/* set RecordMode*/
	void setRecordMode(const bool activate);
	void setEventMode(const bool activate);

	/* get RecordMode*/
	bool isRecordModeActive();

	/* mute audio */
	void muteAudio(const bool mute);

	/* set audio volume */
	void setVolume(const unsigned int left, const unsigned int right);
	void getVolume(unsigned int *left, unsigned int *right);

	/* get dvb transmission type */
	delivery_system_t getDeliverySystem(void);

	void zaptoNvodSubService(const int num);

	/* send diseqc 1.2 motor command */
	void sendMotorCommand(uint8_t cmdtype, uint8_t address, uint8_t cmd, uint8_t num_parameters, uint8_t param1, uint8_t param2);

	/****************************************/
	/*					*/
	/* Scanning stuff			*/
	/*					*/
	/****************************************/
	/* start TS-Scan */
	bool setConfig(Zapit_config Cfg);
	void getConfig(Zapit_config * Cfg);
	bool Rezap();
	bool startScan(int scan_mode);
	bool stopScan();
	/* start manual scan */
	bool scan_TP(TP_params TP);
	bool scan_blind(int scan_mode, int startfreq, int endfreq, int rate, int pol, int tone);
	void getBlindFreqsAVL2108 (int scan_mode,int init_blind,char* startFreq,char* endFreq,char* pol,char* tone, std::list<TP_params> &listTP);
	void getBlindFreqsSTV090x (int startfreq, int endfreq, int symrate,
			int step, unsigned int scan_v, unsigned int scan_h, int lof,
			unsigned int interactive, int fec, unsigned int adapter,
			unsigned int verbose, int delsys,
			unsigned int monitor, unsigned int polarity, int retune,
			unsigned int monitor_retune, int tone, std::list<TP_params> &listTP);



	/* query if ts-scan is ready - response gives status */
	bool isScanReady(unsigned int &satellite, unsigned int &processed_transponder, unsigned int &transponder, unsigned int &services );

	/* query possible satellits*/
	void getScanSatelliteList( SatelliteList& satelliteList );

	/* tell zapit which satellites to scan*/
	void setScanSatelliteList( ScanSatelliteList& satelliteList );

	/* tell zapit stored satellite positions in diseqc 1.2 motor */
	void setScanMotorPosList( ScanMotorPosList& motorPosList );

	/* set diseqcType*/
	void setDiseqcType(const diseqc_t diseqc);

	/* set diseqcRepeat*/
	void setDiseqcRepeat(const uint32_t repeat);

	/* set diseqcRepeat*/
	void setScanBouquetMode(const bouquetMode mode);

	/* set Scan-Type for channel search */
  	void setScanType(const scanType mode);

	/* get FrontEnd Signal Params */ 
	void getFESignal (struct responseFESignal& f);

	/****************************************/
	/*					*/
	/* Bouquet editing functions		*/
	/*					*/
	/****************************************/

	/* adds bouquet at the end of the bouquetlist*/
	void addBouquet(const char * const name); // UTF-8 encoded

	/* moves a bouquet from one position to another */
	/* bouquets are numbered starting at 0 */
	void moveBouquet(const unsigned int bouquet, const unsigned int newPos);
	/* deletes a bouquet with all its channels */
	/* bouquets are numbered starting at 0 */
	void deleteBouquet(const unsigned int bouquet);

	/* assigns new name to bouquet*/
	/* bouquets are numbered starting at 0 */
	void renameBouquet(const unsigned int bouquet, const char * const newName); // UTF-8 encoded

	/* moves a channel of a bouquet from one position to another, channel lists begin at position=1*/
	/* bouquets are numbered starting at 0 */
	void moveChannel(const unsigned int bouquet, unsigned int oldPos, unsigned int newPos, channelsMode mode = MODE_CURRENT);

	// -- check if Bouquet-Name exists (2002-04-02 rasc)
	// -- Return bq_id or -1
	/* bouquets are numbered starting at 0 */
	signed int existsBouquet(const char * const name); // UTF-8 encoded


	// -- check if Channel already in Bouquet (2002-04-05 rasc)
	// -- Return true/false
	/* bouquets are numbered starting at 0 */
	bool  existsChannelInBouquet(const unsigned int bouquet, const t_channel_id channel_id);


	/* adds a channel at the end of then channel list to specified bouquet */
	/* same channels can be in more than one bouquet */
	/* bouquets can contain both tv and radio channels */
	/* bouquets are numbered starting at 0 */
	void addChannelToBouquet(const unsigned int bouquet, const t_channel_id channel_id);

	/* removes a channel from specified bouquet */
	/* bouquets are numbered starting at 0 */
	void removeChannelFromBouquet(const unsigned int bouquet, const t_channel_id channel_id);

	/* set a bouquet's lock-state*/
	/* bouquets are numbered starting at 0 */
	void setBouquetLock(const unsigned int bouquet, const bool lock);

	/* set a bouquet's hidden-state*/
	/* bouquets are numbered starting at 0 */
	void setBouquetHidden(const unsigned int bouquet, const bool hidden);

	/* renums the channellist, means gives the channels new numbers */
	/* based on the bouquet order and their order within bouquets */
	/* necessarily after bouquet editing operations*/
	void renumChannellist();

	/* saves current bouquet configuration to bouquets.xml */
	void saveBouquets();

	/****************************************/
	/*					*/
	/* blah functions			*/
	/*					*/
	/****************************************/

	void setStandby(const bool enable);
	void startPlayBack();
	void stopPlayBack();
	void lockPlayBack();
	void unlockPlayBack();
	bool tune_TP(TP_params TP);
	bool isPlayBackActive();
	void setDisplayFormat(const video_display_format_t mode);
	void setAudioMode(int mode);
	void getAudioMode(int * mode);
	void setVideoSystem(int video_system);

	/****************************************/
	/*					*/
	/* Event functions			*/
	/*					*/
	/****************************************/

	/*
	  ein beliebiges Event anmelden
	*/
	void registerEvent(const unsigned int eventID, const unsigned int clientID, const char * const udsName);

	/*
	  ein beliebiges Event abmelden
	*/
	void unRegisterEvent(const unsigned int eventID, const unsigned int clientID);
};

#define PAL	0
#define NTSC	1


#endif
