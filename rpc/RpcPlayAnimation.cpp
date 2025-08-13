#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"
#include "state.hpp"
RpcPlayAnimation::RpcPlayAnimation(uint8_t animId)
{
	this->animId = animId;
}

void RpcPlayAnimation::Process()
{
	if (State.BypassVisualTasks) {
		PlayerControl_PlayAnimation((*Game::pLocalPlayer), animId, NULL);
		auto writer = InnerNetClient_StartRpcImmediately((InnerNetClient*)(*Game::pAmongUsClient), (*Game::pLocalPlayer)->fields._.NetId, uint8_t(RpcCalls__Enum::PlayAnimation), SendOption__Enum::None, -1, NULL);
		MessageWriter_WriteByte(writer, animId, NULL);
		MessageWriter_EndMessage(writer, NULL);
		return;
	}
	PlayerControl_RpcPlayAnimation(*Game::pLocalPlayer, animId, NULL);
}