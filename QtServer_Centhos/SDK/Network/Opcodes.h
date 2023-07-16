#ifndef __OPCODES__
#define __OPCODES__

#include "../Singleton/Singleton.h"

class OpcodeHandler;
class Packet;
class TcpClient;

// Define packet opcodes
enum Opcodes
{
	MSG_NONE,
	CMSG_CONNECT_CHALLENGE_REQUEST    =   0x0001,
	SMSG_CONNECT_CHALLENGE_RESPONSE   =   0x0002,
	CMSG_CONNECT_CLIENT_LIST_REQ      =   0X0003,
	SMSG_CONNECT_CLIENT_LIST_RESULT   =   0x0004,
	MAX_OPCODES
};

enum SessionStatus
{
	STATUS_NULL,
	STATUS_NOT_LOGGED,
	STATUS_LOGGED
};

struct OpcodeStruct
{
	quint32 id;
	char const* name;
	SessionStatus status;
	void (OpcodeHandler::* handler)(Packet& pPacket, TcpClient* pClient);

};

class OpcodeStore
{
	DECLARE_SINGLETON(OpcodeStore)
public:
	void BuildOpcodeList();
	void StoreOpcode(quint32 pOpcode, char const* pName, SessionStatus pStatus, void (OpcodeHandler::* pHandler)(Packet& pPacket, TcpClient* pClient));
	bool OpcodeExist(quint32 pID);
	OpcodeStruct GetOpcodeData(quint32 pID);

private:
	OpcodeStore(){}
	QMap<quint32, OpcodeStruct> mList;

};



#endif 
