#ifndef ARROW_HPP
#define	ARROW_HPP

namespace robinglut
{

	class arrow
	{
	private:
		float x, y, z;
		float speed, winkel;
		bool start;
		bool start_spannen;
		int start_time;
		int AnzahlPfeile;

	public:
		arrow(float x, float y, float z);
		
		void Animate(int time, float anglex);
		void startAnimate();
		bool stopAnimate();
		void spannen(int time);
		void activeSpannen();
		void stopSpannen();
		float getSpeed();
		int get_arrow_count();

		void display();
	};
}

#endif	/* ARROW_HPP */

