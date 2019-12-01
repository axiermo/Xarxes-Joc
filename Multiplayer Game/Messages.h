#pragma once

enum class ClientMessage
{
	Hello,
	Input,
	WantToDisconnect,
	Ping
};

enum class ServerMessage
{
	Welcome,
	Unwelcome,
	Replication,
	Ping,
	ServerFull
};
