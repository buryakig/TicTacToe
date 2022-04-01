#pragma once

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 860

#define SPLASH_STATE_SHOW_TIME 1.0
#define SPLASH_SCENE_BACKGROUND_FILEPATH	"res/Logo.png"
#define MAIN_MENU_BACKGROUND_FILEPATH		"res/MainMenuBackground.png"
#define GAME_MENU_BACKGROUND_FILEPATH		"res/MainMenuBackground.png"
#define PAUSE_BACKGROUND_FILEPATH			"res/MainMenuBackground.png"
#define MAIN_MENU_TITLE_PATH				"res/MainMenuTitle.png"
#define MAIN_MENU_PLAY_BUTTON				"res/PlayButton.png"
#define MAIN_MENU_PLAY_BUTTON_OUTER			"res/PlayButtonOuter.png"

#define PAUSE_BUTTON						"res/PauseButton.png"
#define RESUME_BUTTON						"res/ResumeButton.png"
#define HOME_BUTTON							"res/HomeButton.png"
#define RETRY_BUTTON						"res/RetryButton.png"

#define GRID_SPRITE_FILEPATH				"res/Grid.png"

#define X_PIECE_FILEPATH					"res/X.png"
#define O_PIECE_FILEPATH					"res/O.png"
#define X_WINNING_PIECE_FILEPATH			"res/XWin.png"
#define O_WINNING_PIECE_FILEPATH			"res/OWin.png"

#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1
#define PLAYER_PIECE X_PIECE
#define AI_PIECE O_PIECE

// States
#define STATE_PLAYING 100
#define STATE_PAUSED 99
#define X_WON 98
#define O_WON 97
#define STATE_PLACING_PIECE 96
#define STATE_AI_PLAYING 95
#define STATE_DRAW 94