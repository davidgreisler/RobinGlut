#include "menu.hpp"
#include "raw_loader.hpp"

#include <iostream>

namespace robinglut
{
	/**
	 * Creates a new menu object.
         */
	menu::menu()
	{
		raw_loader loader;
		this->title = loader.load_file("images/title.raw", 800, 600, false);
	}

	/**
	 * Frees used resources.
         */
	menu::~menu()
	{

	}

	/**
	 * Displays the menu.
         */
	void menu::display()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->title);
		glColor3f(0.886, 0.9333, 0.94);
		glPushMatrix();
		glTranslatef(10.2, 2.5, 2.5);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(1, 0, -10);
		glTexCoord2f(0, 1);
		glVertex3f(1, 15, -10);
		glTexCoord2f(1, 1);
		glVertex3f(1, 15, 5);
		glTexCoord2f(1, 0);
		glVertex3f(1, 0, 5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	/**
	 * Keypress handler.
	 * 
	 * When 1, 2, 3, or 4 is pressed, an event is emitted for the selected
	 * option.
	 * 
         * @param key Pressed key.
         * @param x Ignored.
         * @param y Ignored.
         */
	void menu::on_keypress(unsigned char key, int x, int y)
	{
		switch (key)
		{
			case '1': this->option_selected_event(1); break;
			case '2': this->option_selected_event(2); break;
			case '3': this->option_selected_event(3); break;
			case '4': this->option_selected_event(4); break;
		}

	}
        
        /**
	 * Maus handler.
	 * 
	 * 
         * @param button Button key.
         * @param state right or left.
         * @param x X coordinate
         * @param y Y coordinate
         * 
         * Start: 500, 460 : 500, 400 : 930, 400 : 930, 460
         * Heighscore: 500, 590: 500, 520: 920, 530 : 920, 600
         * Exit: 630, 700: 630, 650: 790, 650 : 790, 700
         */
        void menu::on_mouse(int button, int state, int x, int y){
            // start Game
            if(x > 500 && x < 930 && y > 400 && y < 460)
                this->option_selected_event(1);
            //Exit
            if(x > 630 && x < 790 && y > 650 && y < 700)
                this->option_selected_event(4);
            //Heighscore
            if(x > 630 && x < 790 && y > 700 && y < 790)
                this->option_selected_event(3);

        }
}
