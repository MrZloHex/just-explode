#include "stdio.h"

#include "mine.h"
#include "screen.h"


typedef enum StartMenu_E
{
	NEW_GAME = (int)0,
	SETTINGS = (int)1,
	EXIT  	 = (int)2
} StartMenu;

int
main(int argc, char **argv)
{	
	Screen *screen = screen_initialize();
	StartMenu choice = (StartMenu)screen_start_menu(screen);
	
	if (choice == NEW_GAME)
	{
		screen_deinitialize(screen);
		exit(69);
	}
	else if (choice == SETTINGS)
	{
		
	}
	else if (choice == EXIT)
	{
		screen_deinitialize(screen);
		exit(0);
	}

	return 0;
}