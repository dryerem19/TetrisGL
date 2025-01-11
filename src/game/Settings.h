#pragma once

constexpr int BOARD_COLUMNS = 10;
constexpr int BOARD_ROWS    = 20;

constexpr int CELL_SIZE     = 40;
constexpr int GUI_WIDTH     = 300;
constexpr int WINDOW_WIDTH  = (CELL_SIZE * BOARD_COLUMNS) + GUI_WIDTH;
constexpr int WINDOW_HEIGHT = CELL_SIZE * BOARD_ROWS;
constexpr int GUI_START_X   = WINDOW_WIDTH - GUI_WIDTH;
constexpr int GUI_CENTER_X  = GUI_START_X + (GUI_WIDTH / 2);
constexpr int GUI_CENTER_Y  = WINDOW_HEIGHT / 2;

/* Текст рисуется относительно низа! */
constexpr int SCORE_Y = WINDOW_HEIGHT - 50;
constexpr int NEXT_Y  = SCORE_Y - 200;

constexpr int CONTROL_TEXT_Y = 200;
constexpr int NEXT_TETRAMINO_Y = GUI_CENTER_Y - 150;

constexpr int TETRAMINOES[7][4] = {
	1, 3, 5, 7, // I 
	2, 4, 5, 7, // S 
	3, 5, 4, 6, // Z
	3, 5, 4, 7, // T
	2, 3, 5, 7, // J
	3, 5, 7, 6, // L
	2, 3, 4, 5  // O
};