#include "level2.hpp"

namespace robinglut
{
	level_2::level_2(robinglut::player* game_player)
		: level(game_player)
	{
		this->targets.push_back(new robinglut::target(50,10,0,5.0,5.0, this->butt_texture));
		this->targets.push_back(new robinglut::target(50,10,10,5.0,5.0, this->butt_texture));
		this->targets.push_back(new robinglut::target(50,10,-10,5.0,5.0, this->butt_texture));
		this->targets.push_back(new robinglut::target(50,10,-20,5.0,5.0, this->butt_texture));
		this->targets.push_back(new robinglut::target(50,10,20,5.0,5.0, this->butt_texture));
		
		this->player->add_arrows(5);
		
		this->initialize();
	}
}
