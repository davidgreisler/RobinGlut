#include "level4.hpp"

namespace robinglut
{
	level_4::level_4(robinglut::player* game_player)
		: level(game_player)
	{
                target* animate = new robinglut::target(50,10,0,5.0,5.0, this->butt_texture);
                animate->set_animated(10);
		this->targets.push_back(animate);
		
		
		this->player->add_arrows(3);
		
		this->initialize();
	}
}
