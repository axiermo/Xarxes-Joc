#include "Networks.h"
#include "ReplicationManagerServer.h"

void ReplicationManagerServer::create(uint32 networkId)
{
	replicationCommands[networkId] = ReplicationAction::Create;
}

void ReplicationManagerServer::update(uint32 networkId)
{
	std::map<uint32, ReplicationAction>::iterator iterator = replicationCommands.find(networkId);
	if (iterator == replicationCommands.end())
	{
		replicationCommands[networkId] = ReplicationAction::Update;
	}
}

void ReplicationManagerServer::destroy(uint32 networkId)
{
	replicationCommands[networkId] = ReplicationAction::Destroy;
}

void ReplicationManagerServer::write(OutputMemoryStream& packet)
{
	for (std::map<uint32, ReplicationAction>::iterator it_rc = replicationCommands.begin(); it_rc != replicationCommands.end(); ++it_rc)
	{
		if (it_rc->second == ReplicationAction::Create)
		{
			GameObject* object = nullptr;
			object = App->modLinkingContext->getNetworkGameObject(it_rc->first);

			if (object)
			{
				packet << it_rc->first;
				packet << it_rc->second;

				packet << object->position.x;
				packet << object->position.y;
				packet << object->angle;
				packet << object->size.x;
				packet << object->size.y;

				std::string texture(object->texture->filename);
				packet << texture;
			}
		}
		else if (it_rc->second == ReplicationAction::Update)
		{
			GameObject* object = nullptr;
			object = App->modLinkingContext->getNetworkGameObject(it_rc->first);

			if (object)
			{
				packet << it_rc->first;
				packet << it_rc->second;

				packet << object->position.x;
				packet << object->position.y;
				packet << object->angle;
			}
		}
		else if (it_rc->second == ReplicationAction::Destroy)
		{
			packet << it_rc->first;
			packet << it_rc->second;
		}
	}

	replicationCommands.clear();
}