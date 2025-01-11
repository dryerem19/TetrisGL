#pragma once

#include <chrono>

#include "../core/audio/Audio.h"

#include "Settings.h"
#include "../types/direction.h"

#include "Tetramino.h"

class GameManager final
{
	friend class Tetramino;
private:
	int _board[BOARD_ROWS][BOARD_COLUMNS] = { 0 };
	std::unique_ptr<Tetramino> _activeTetramino;
	std::unique_ptr<Tetramino> _ghostTetramino;
	std::unique_ptr<Tetramino> _nextTetramino;
	bool _loaded{ false };

	int dropInterval = 1000;
	std::chrono::steady_clock::time_point lastDropTime = std::chrono::steady_clock::now();

	/* Ресурсы */
	AudioSource _source;
	AudioSource _themeSource;
	std::shared_ptr<AudioClip> _moveClip;
	std::shared_ptr<AudioClip> _themeClip;
	std::shared_ptr<AudioClip> _rotateClip;
	std::shared_ptr<AudioClip> _landedClip;
	std::shared_ptr<AudioClip> _lineClearClip;
	std::shared_ptr<AudioClip> _4LinesClearClip;

	Sprite _ghostSprite;
	Sprite _gridSprite;
	Sprite _sprites[7];

	Text _controlText;
	Text _scoreLabel;
	Text _nextLabel;
	Text _scoreText;
	std::shared_ptr<Font> _font;

	/* Количество очков за каждую линию (индекс - количество удаленных линий) */
	int _points[5] = {
		0, 100, 300, 700, 1500
	};

	/* Текущее количетсво очков */
	int _score = 0;

	/* Скорость свободного падения фигуры */
	int _speed = 1;

public:
	void MakeTetramino(int type, bool next = false);
	void MoveTetramino(Direction direction);
	void Draw(Renderer& renderer);
	std::string GetScore() const;
	void SpawnTetramino();
	bool CheckCollide(Tetramino* tetromino) const;
	bool IsGameOver() const;
	void ClearLines();
	void InitGame();
	void Update();
};