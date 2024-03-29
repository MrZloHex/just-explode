#ifndef __CHOICES_H__
#define __CHOICES_H__


typedef enum StartMenu_E
{
	SM_NEW_GAME  = 0,
	SM_EXIT  	 = 1
} StartMenu;


typedef enum SetupGameMenu_E
{
	SGM_PLAY = 2,
	SGM_BACK = 3
} SetupGameMenu;


typedef enum GameResult_E
{
	GR_GAME_OVER,
	GR_GAME_WIN,
	GR_PAUSE
} GameResult;


typedef enum GameFinishMenu_E
{
	GFM_NEW_GAME,
	GFM_EXIT
} GameFinishMenu;

typedef enum GamePauseMenu_E
{
	GPM_RESUME,
	GPM_NEW_GAME,
	GPM_EXIT
} GamePauseMenu;

#endif /* __CHOICES_H__ */