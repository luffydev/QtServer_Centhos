#ifndef __OPCODE_HANDLER__
#define __OPCODE_HANDLER__

class Packet;
class TcpClient;
class Logger;

class OpcodeHandler
{

public:
	
	typedef void (OpcodeHandler::* HandlerFunction)(Packet&, TcpClient*);
	OpcodeHandler();

	void Handle_NULL(Packet& pPacket, TcpClient* pSocket);
	void Handle_Connect_Challenge_Request(Packet& pPacket, TcpClient* pSocket);

private:
	Logger* mLogger;

};

#endif
