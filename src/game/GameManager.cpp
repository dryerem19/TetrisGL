#include "GameManager.h"

#include "../core/input/Input.h"
#include "../core/ResourceManager.h"
#include <thread>

void GameManager::MakeTetramino(int type, bool next)
{
	/* Идентификатор должен быть больше 0, чтобы можно было отличить блок от пустой клетки */
	int id = type + 1;

	/* Создаем фигуру соответсвующую типу */
	auto& ptr = next ? _nextTetramino : _activeTetramino;
	ptr = std::make_unique<Tetramino>(_sprites[type]);
	ptr->id = id;

	for (int i = 0; i < 4; ++i) {
		ptr->blocksPositions[i].x = TETRAMINOES[type][i] % 2;
		ptr->blocksPositions[i].y = TETRAMINOES[type][i] / 2;
	}

	if (next) {
		for (int i = 0; i < 4; ++i) {
			_nextTetramino->blocksPositions[i].x *= CELL_SIZE;
			_nextTetramino->blocksPositions[i].y *= CELL_SIZE;
			_nextTetramino->blocksPositions[i].x += GUI_CENTER_X - CELL_SIZE;
			_nextTetramino->blocksPositions[i].y += NEXT_TETRAMINO_Y;
		}
	}
}

void GameManager::MoveTetramino(Direction direction)
{
	int dx{ 0 };
	bool rotate = false;

	if (direction == Direction::Left) {
		dx = -1;
	}
	else if (direction == Direction::Right) {
		dx = 1;
	}
	else if (direction == Direction::Up) {
		rotate = true;
	}
	else if (direction == Direction::Down) {
		_speed += 1;
	}

	// Перемещаем фигуру в новую позицию и запоминаем текущую
	for (int i = 0; i < 4; ++i) {
		_activeTetramino->prevBlocksPositions[i] = _activeTetramino->blocksPositions[i];
		_activeTetramino->blocksPositions[i].x += dx;
	}

	// Игрок хочет повернуть фигуру
	if (rotate) {
		_activeTetramino->Rotate();
	}

	// Если фигура оказалась за пределами игрового поля, перемещаем её назад
	if (!this->CheckCollide(_activeTetramino.get())) {
		for (int i = 0; i < 4; ++i) {
			_activeTetramino->blocksPositions[i] = _activeTetramino->prevBlocksPositions[i];
		}
	}
	else {
		if (!rotate) {
			_source.PlayOneShot(_moveClip);
		}
		else {
			_source.PlayOneShot(_rotateClip);
		}
	}

	/* Добавляем задержку, чтобы мы не могли слишком быстро передвигаться */
	std::this_thread::sleep_for(std::chrono::milliseconds(60));
}

void GameManager::Draw(Renderer& renderer)
{
	/* Рисуем падающую фигуру */
	_activeTetramino->Draw(renderer);

	/* Рисуем призрачную фигуру */
	_ghostTetramino->Draw(renderer);

	/* Рисуем игровое поле */
	for (int y = 0; y < BOARD_ROWS; ++y) {
		for (int x = 0; x < BOARD_COLUMNS; ++x) {

			const int id = _board[y][x] - 1;
			auto& sprite = (_board[y][x] == 0) ? _gridSprite : _sprites[id];

			sprite.SetPosition({ x * CELL_SIZE, y * CELL_SIZE });
			renderer.DrawSprite(&sprite);
		}
	}
		
	/* Render GUI */
	renderer.DrawText(_scoreLabel);

	const auto& scoreText = this->GetScore();
	_scoreText.SetText(scoreText);
	_scoreText.SetPosition({ GUI_CENTER_X - _scoreText.GetHalfWidth(), SCORE_Y - 100 });

	renderer.DrawText(_scoreText);
	renderer.DrawText(_nextLabel);
	renderer.DrawText(_controlText);

	/* Рисуем 'следующее' тетрамино в окне GUI */
	for (int i = 0; i < 4; ++i) {
		_nextTetramino->tile.SetPosition({ _nextTetramino->blocksPositions[i].x, _nextTetramino->blocksPositions[i].y });
		renderer.DrawSprite(&_nextTetramino->tile);
	}
}

std::string GameManager::GetScore() const
{
	return std::to_string(_score);
}

void GameManager::SpawnTetramino()
{
	if (!_nextTetramino) {
		this->MakeTetramino(rand() % 7);
	}
	else {
		this->MakeTetramino(_nextTetramino->id - 1);
	}

	this->MakeTetramino(rand() % 7, true);

	/* Создаём фигуру-призрак */
	_ghostTetramino = std::make_unique<Tetramino>(_ghostSprite);
}

bool GameManager::CheckCollide(Tetramino* tetromino) const
{
	for (int i = 0; i < 4; ++i) {

		int x = tetromino->blocksPositions[i].x;
		int y = tetromino->blocksPositions[i].y;

		if (x < 0 || x >= BOARD_COLUMNS || y >= BOARD_ROWS) {
			return false;
		}
		else if (_board[y][x]) {
			return false;
		}
	}

	return true;
}

bool GameManager::IsGameOver() const
{
	for (auto& pos : _activeTetramino->blocksPositions) {
		if (_board[pos.y][pos.x]) {
			return true;
		}
	}

	return false;
}

void GameManager::ClearLines()
{
	int targetRow = BOARD_ROWS - 1;
	int linesCleared = 0;

	for (int iRow = targetRow; iRow > 0; iRow--) {

		/* Считаем количество заполненных клеток в строке */
		int count = 0;
		for (int iColumn = 0; iColumn < BOARD_COLUMNS; ++iColumn) {

			/* Проверяем, занята ли клетка */
			if (_board[iRow][iColumn]) {
				count++;
			}

			_board[targetRow][iColumn] = _board[iRow][iColumn];
		}

		/* Если строка не заполнена, переходим к следующей */
		if (count < BOARD_COLUMNS) {
			targetRow--;
		}
		else {
			linesCleared++;
		}
	}

	if (linesCleared > 0 && linesCleared != 4) {
		_source.PlayOneShot(_lineClearClip);
	}
	else if (linesCleared == 4) {
		_source.PlayOneShot(_4LinesClearClip);
	}

	/* Увеличиваем количество очков */
	_score += _points[linesCleared];
}

void GameManager::InitGame()
{
	/* Инициализируем пустое игровое поле */
	for (int i = 0; i < BOARD_ROWS; ++i) {
		for (int j = 0; j < BOARD_COLUMNS; ++j) {
			_board[i][j] = 0;
		}
	}

	/* Обнуляем количество очков */
	_score = 0;

	/* Загружаем ресурсы */
	if (!_loaded) {

		/* Обращаемся к менеджеру ресурсов */
		auto& rm = ResourceManager::GetInstance();
		
		/* Загружаем тайлы блоков */
		auto& gridTexture   = rm.LoadTexture("assets/Grid.png");
		auto& cyanTexture   = rm.LoadTexture("assets/Cyan.png");
		auto& blueTexture   = rm.LoadTexture("assets/Blue.png");
		auto& orangeTexture = rm.LoadTexture("assets/Orange.png");
		auto& yellowTexture = rm.LoadTexture("assets/Yellow.png");
		auto& greenTexture  = rm.LoadTexture("assets/Green.png");
		auto& purpleTexture = rm.LoadTexture("assets/Purple.png");
		auto& redTexture    = rm.LoadTexture("assets/Red.png");
		auto& ghostTexture  = rm.LoadTexture("assets/Ghost.png");

		/* Устанавливаем загруженные тайлы в спрайты блоков */
		_ghostSprite.SetTexture(ghostTexture);
		_gridSprite.SetTexture(gridTexture);
		_sprites[0].SetTexture(cyanTexture);
		_sprites[1].SetTexture(greenTexture);
		_sprites[2].SetTexture(redTexture);
		_sprites[3].SetTexture(purpleTexture);
		_sprites[4].SetTexture(blueTexture);
		_sprites[5].SetTexture(orangeTexture);
		_sprites[6].SetTexture(yellowTexture);

		/* Устанавливаем размер тайла */
		for (int i = 0; i < 7; ++i) {
			_sprites[i].SetSize({ CELL_SIZE, CELL_SIZE });
		}

		_ghostSprite.SetSize({ CELL_SIZE, CELL_SIZE });
		_gridSprite.SetSize({ CELL_SIZE, CELL_SIZE });

		/* Загружаем звуки */
		_moveClip        = rm.LoadAudioClip("assets/audio/move.wav");
		_themeClip       = rm.LoadAudioClip("assets/audio/theme.wav");
		_landedClip      = rm.LoadAudioClip("assets/audio/landed.wav");
		_rotateClip      = rm.LoadAudioClip("assets/audio/rotate.wav");
		_lineClearClip   = rm.LoadAudioClip("assets/audio/line_clear.wav");
		_4LinesClearClip = rm.LoadAudioClip("assets/audio/4_lines_clear.wav");

		/* Загружаем шрифт */
		_font = Font::Create("assets/fonts/Retro Gaming.ttf", 14);
		
		/* Создаём текстовую метку 'SCORE' */
		_scoreLabel.SetText("SCORE");
		_scoreLabel.SetFont(_font);
		_scoreLabel.SetSize(28);
		_scoreLabel.SetPosition({ GUI_CENTER_X - _scoreLabel.GetHalfWidth(), SCORE_Y});

		/* Создаём текст для вывода количества очков */
		_scoreText.SetFont(_font);
		_scoreText.SetSize(28);

		_nextLabel.SetText("NEXT");
		_nextLabel.SetFont(_font);
		_nextLabel.SetSize(28);
		_nextLabel.SetPosition({ GUI_CENTER_X - _nextLabel.GetHalfWidth(), NEXT_Y });

		_controlText.SetText("CONTROL");
		_controlText.SetFont(_font);
		_controlText.SetSize(28);
		_controlText.SetPosition({ GUI_CENTER_X - _controlText.GetHalfWidth(), CONTROL_TEXT_Y });

		/* Устанавливаем флаг, что ресурсы загружены */
		_loaded = true;
	}

	/* Спавним первую фигуру */
	this->SpawnTetramino();

	/* Запускаем фоновую музыку */
	{
		std::thread thread([&]() {
			_themeSource.SetLoop(true);
			_themeSource.SetVolume(0.2f);
			_themeSource.SetClip(_themeClip);
			_themeSource.Play();
			});

		thread.detach();
	}
}

void GameManager::Update()
{ 
	/* Обновляем призрачную фигурку */
	std::copy(std::begin(_activeTetramino->blocksPositions), std::end(_activeTetramino->blocksPositions), std::begin(_ghostTetramino->blocksPositions));
	std::copy(std::begin(_activeTetramino->prevBlocksPositions), std::end(_activeTetramino->prevBlocksPositions), std::begin(_ghostTetramino->prevBlocksPositions));
	while (true) {
		_ghostTetramino->MoveDown();

		if (!this->CheckCollide(_ghostTetramino.get())) {
			_ghostTetramino->MoveBack();
			break;
		}
	}

	// Вычисляем время с последнего падения
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastDropTime).count();

	// Обрабатываем пользовательский ввод
	if (Input::GetKey(KeyCode::W) || Input::GetKey(KeyCode::UpArrow)) {
		this->MoveTetramino(Direction::Up);
	}

	if (Input::GetKey(KeyCode::A) || Input::GetKey(KeyCode::LeftArrow)) {
		this->MoveTetramino(Direction::Left);
	}

	if (Input::GetKey(KeyCode::D) || Input::GetKey(KeyCode::RightArrow)) {
		this->MoveTetramino(Direction::Right);
	}

	if (Input::GetKey(KeyCode::S) || Input::GetKey(KeyCode::DownArrow)) {
		dropInterval = 0;
	}

	if (elapsedTime >= dropInterval) {
		lastDropTime = currentTime;

		// Двигаем фигуру вниз каждый кадр
		_activeTetramino->MoveDown();

		// Если фигура столкнулась, добавляем ее на поле
		if (!this->CheckCollide(_activeTetramino.get())) {
			for (int i = 0; i < 4; ++i) {
				int x = _activeTetramino->prevBlocksPositions[i].x;
				int y = _activeTetramino->prevBlocksPositions[i].y;
				_board[y][x] = _activeTetramino->id;
			}

			_source.PlayOneShot(_landedClip);

			// Спавним новую фигуру
			this->SpawnTetramino();
		}

		this->ClearLines();
		dropInterval = 1000;
	}
}
