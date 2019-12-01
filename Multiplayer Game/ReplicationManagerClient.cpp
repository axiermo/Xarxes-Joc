#include "Networks.h"

void ReplicationManagerClient::read(const InputMemoryStream& packet)
{
	while (packet.RemainingByteCount() > 0)
	{
		uint32 networkId;
		packet >> networkId;

		ReplicationAction action;
		packet >> action;

		if (action == ReplicationAction::Create)
		{
			GameObject* object = nullptr;
			object = Instantiate();

			App->modLinkingContext->registerNetworkGameObjectWithNetworkId(object, networkId);

			std::string texture;

			packet >> object->position.x;
			packet >> object->position.y;
			packet >> object->angle;
			packet >> object->size.x;
			packet >> object->size.y;
			packet >> texture;

			object->texture = App->modTextures->loadTexture(texture.c_str());

		}
		else if (action == ReplicationAction::Update)
		{
			GameObject* object = nullptr;
			object = App->modLinkingContext->getNetworkGameObject(networkId);


			packet >> object->position.x;
			packet >> object->position.y;
			packet >> object->angle;

		}
		else
		{
			GameObject* object = nullptr;
			object = App->modLinkingContext->getNetworkGameObject(networkId);

			if (object)
			{
				App->modLinkingContext->unregisterNetworkGameObject(object);

				Destroy(object);
			}
		}
	}
}