#include "level1.hpp"

namespace robinglut
{
	level_1::level_1(robinglut::player* game_player)
		: level(game_player)
	{
		this->targets.push_back(new robinglut::target(50,10,0,5.0,5.0, this->butt_texture));
		this->targets.push_back(new robinglut::target(50,10,10,5.0,5.0, this->butt_texture));
		this->targets.push_back(new robinglut::target(50,10,-10,5.0,5.0, this->butt_texture));
		
		this->initialize();
	}
}
