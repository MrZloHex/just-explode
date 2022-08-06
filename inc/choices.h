#ifndef __CHOICES_H__
#define __CHOICES_H__


#define START_MENU_STRINGS "New Game", "Continue", "Exit"

typedef enum StartMenu_E
{
	SM_NEW_GAME  = 0,
    SM_CONTINUE  = 1,
	SM_EXIT  	 = 2
} StartMenu;


typedef enum SetupGameMenu_E
{
	SGM_PLAY = 2,
	SGM_BACK = 3
} SetupGameMenu;



#endif /* __CHOICES_H__ */