#pragma once
namespace game
{
	namespace config
	{
		//resources
		static const char BORDER_SYMB_HORISONTAL = '=';
		static const char BORDER_SYMB_VERTICAL = '|';

		static const char MAP_EMPTY_SYMB = ' ';
		static const std::string SCORE_LABEL = "SCORE: ";
		static const char SNAKE_BODY_SYMB = '*';
		static const char SNAKE_HEAD_SYMB = '@';
		static const char BONUS_SYMB = '+';

		//menu scenes
		static const char MENU_CURSOR = '*';
		static const std::string NEW_GAME_LABEL = "NEW GAME";
		static const std::string MENU_LABEL = "MENU:";
		static const std::string DEMO_MOVE_LABEL = "DEMO MODE";
		static const std::string EXIT_LABEL = "EXIT";

		//keys
		static const int INPUT_KEY_TOP = 72;
		static const int INPUT_KEY_TOP_ALTERNATIVE = 119;
		static const int INPUT_KEY_DOWN = 80;
		static const int INPUT_KEY_DOWN_ALTERNATIVE = 115;
		static const int INPUT_KEY_LEFT = 75;
		static const int INPUT_KEY_LEFT_ALTERNATIVE = 97;
		static const int INPUT_KEY_RIGHT = 77;
		static const int INPUT_KEY_RIGHT_ALTERNATIVE = 100;

		static const int INPUT_KEY_ENTER = 13;

		//level default config
		static const size_t MAX_MAP_WIDTH = 100;
		static const size_t MAX_MAP_HEIGHT = 30;
		static const int START_SNAKE_POSITION_X = 5;
		static const int START_SNAKE_POSITION_Y = 5;
		static const int DEFAULT_GAME_UPDATE_SPEED = 100;
		static const int DEFAULT_GAME_KEYBOARD_READ_SPEED = 5;
		static const int SPEED_DIFFICULT_STEP = 10;

		static const size_t GAME_MAX_WIN_H = 550;
		static const size_t GAME_MAX_WIN_W = 1000;

		static const size_t MENU_MAX_WIN_H = 200;
		static const size_t MENU_MAX_WIN_W = 800;
		static const size_t WIN_UPDATE_TIMEOUT = 10000;

	}
}