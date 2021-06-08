//packet.cpp :葛电 家胶颇老篮 pch.h颇老阑 力老刚历 include

#include "pch.h"			//pre complie header 
#include "packet.h"

PACKETNEWMEMBER PACKETNEWMEMBER::CreatePacket(const char* _name,
	const char* _id, const char* _pw)
{
	PACKETNEWMEMBER packet;
	
	packet.flag = PACK_NEWMEMBER;
	strcpy_s(packet.id, sizeof(packet.id), _id);
	strcpy_s(packet.pw, sizeof(packet.pw), _pw);
	strcpy_s(packet.name, sizeof(packet.name), _name);

	return packet;
}

PACKETNEWMEMBER PACKETNEWMEMBER::CreatePacket(const char* _id, const char* _pw)
{
	PACKETNEWMEMBER packet;

	packet.flag = PACK_LOGIN;
	strcpy_s(packet.id, sizeof(packet.id), _id);
	strcpy_s(packet.pw, sizeof(packet.pw), _pw);

	return packet;
}

PACKETLOGOUT PACKETLOGOUT::CreatePacket(const char* _id)
{
	PACKETLOGOUT packet;

	packet.flag = PACK_LOGOUT;
	strcpy_s(packet.id, sizeof(packet.id), _id);

	return packet;
}

PACKETSHORTMESSAGE PACKETSHORTMESSAGE::CreatePacket(const char* _name, const char* _msg)
{
	PACKETSHORTMESSAGE packet;
	packet.flag = PACK_SHORTMESSAGE;
	strcpy_s(packet.name, sizeof(packet.name), _name);
	strcpy_s(packet.msg, sizeof(packet.msg), _msg);

	CTime curtime = CTime::GetCurrentTime();
	packet.hour = curtime.GetHour();
	packet.min = curtime.GetMinute();
	packet.second = curtime.GetSecond();

	return packet;
}

PACKETSHORTMESSAGE PACKETSHORTMESSAGE::CreatePacket(const char* _name, const char* _msg,
	bool dummy)
{
	PACKETSHORTMESSAGE packet;
	packet.flag = PACK_MEMOMESSAGE;
	strcpy_s(packet.name, sizeof(packet.name), _name);
	strcpy_s(packet.msg, sizeof(packet.msg), _msg);

	CTime curtime = CTime::GetCurrentTime();
	packet.hour = curtime.GetHour();
	packet.min = curtime.GetMinute();
	packet.second = curtime.GetSecond();

	return packet;
}