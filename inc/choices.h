#ifndef __CHOICES_H__
#define __CHOICES_H__


#define START_MENU_STRINGS "New Game", "Settings", "Exit"

typedef enum StartMenu_E
{
	SM_NEW_GAME  = (int)0,
	SM_SETTINGS  = (int)1,
	SM_EXIT  	 = (int)2
} StartMenu;



#endif /* __CHOICES_H__ */