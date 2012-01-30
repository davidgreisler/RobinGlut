#include "level3.hpp"

namespace robinglut
{
	level_3::level_3(robinglut::player* game_player)
		: level(game_player)
	{
		this->targets.push_back(new robinglut::target(50,10,-5,3.0,3.0, this->butt_texture));
		this->targets.push_back(new robinglut::target(50,10,5,3.0,3.0, this->butt_texture));
		
		this->player->add_arrows(3);
		
		this->initialize();
	}
}
