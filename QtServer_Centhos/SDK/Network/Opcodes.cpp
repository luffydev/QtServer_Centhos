#include "OpcodeHandler.h"
#include "Packet.h"
#include "Client.h"
#include "Opcodes.h"


void OpcodeStore::BuildOpcodeList()
{
	/*0x0000*/ StoreOpcode(MSG_NONE,                                "MSG_NONE",                           STATUS_NOT_LOGGED,    &OpcodeHandler::Handle_NULL);
	/*0x0001*/ StoreOpcode(CMSG_CONNECT_CHALLENGE_REQUEST,          "CMSG_CONNECT_CHALLENGE_REQUEST",     STATUS_NOT_LOGGED,    &OpcodeHandler::Handle_Connect_Challenge_Request);
	/*0x0002*/ StoreOpcode(SMSG_CONNECT_CHALLENGE_RESPONSE,         "SMSG_CONNECT_CHALLENGE_RESPONSE",    STATUS_NOT_LOGGED,    &OpcodeHandler::Handle_NULL);
}

void OpcodeStore::StoreOpcode(quint32 pOpcode, char const* pName, SessionStatus pStatus, void (OpcodeHandler::* pHandler)(Packet& pPacket, TcpClient* pClient))
{
	OpcodeStruct lStruct;
	
	lStruct.id = pOpcode;
	lStruct.name = pName;
	lStruct.status = pStatus;
	lStruct.handler = pHandler;

	mList.insert(pOpcode, lStruct);
}

bool OpcodeStore::OpcodeExist(quint32 pID)
{
	return mList.contains(pID);
}

OpcodeStruct OpcodeStore::GetOpcodeData(quint32 pID)
{
	OpcodeStruct lStruct = {};

	if (!mList.contains(pID))
		return lStruct;

	return mList[pID];
}
