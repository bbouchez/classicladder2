// monitor_transfer.h

#ifndef __MONITOR_TRANSFER_H__
#define __MONITOR_TRANSFER_H__

#include "cJSON.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct StrFileTransfer
{
	char FileName[ 400 ];
	char IsSendTransfer; //send or received file
	FILE * pFileTransferDesc;
	int NumBlock;
	int NbrTotalBlocks;
	int SizeBlock; // size of real datas file (before base64 encoding)
	int NumFile;
	int SubNumFile;
	int StartTransferDone; // for the first time...
	char AskToAbort;
}StrFileTransfer;

void InitMonitorTransferFile( void );

void TransferMasterStart( void );
void TransferMasterAskToAbort( void );
StrFileTransfer * GetPtrFileTransForMaster( void );

void SecurityForAbortedTransferToSlave( void );

void CloseFileTransfer( StrFileTransfer * pFileTrans );
char StartToReadFileToSend( StrFileTransfer * pFileTrans );
char StartToWriteFileToReceive( StrFileTransfer * pFileTrans );

char * MonitorCreateRequestFileTransfer( void );
void MonitorParseResponseFileTransfer( cJSON *JsonRoot, char SlaveMode );

#ifdef __cplusplus
}
#endif

#endif
