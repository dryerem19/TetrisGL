#include "Text.h"

void Text::SetFont(const std::shared_ptr<Font>& font)
{
	_font = font;
}

void Text::SetText(const std::string& text)
{
	if (!text.empty()) {
		_text = text;
	}
}

void Text::SetSize(int size)
{
	if (size > 0) {
		_size = size;
	}
}

void Text::SetColor(const glm::vec4& color)
{
	_color = color;
}

void Text::SetPosition(const glm::ivec2& position)
{
	_position = position;
}

const std::shared_ptr<Font>& Text::GetFont() const
{
	return _font;
}

int Text::GetWidth() const
{
	if (!_font) {
		return 0;
	}

	float result = 0.0f;
	float rowWidth = 0.0f;
	const float scale = static_cast<float>(_size) / static_cast<float>(_font->GetSize());

	for (int i = 0; i < static_cast<int>(_text.length()); ++i) {
		if (_text[i] == '\n' || _text[i] == '\r') {
			continue;
		}

		bool lastCharacterInRow = i == _text.length() - 1 || _text[i + 1] == '\n' || _text[i + 1] == '\r';
		const auto& props = _font->GetProperties(_text[i]);
		if (!lastCharacterInRow) {
			rowWidth += props.advanceX * scale;
			continue;
		}

		rowWidth += (props.bearingX + props.width) * scale;
		result = std::max(result, rowWidth);
		rowWidth = 0.0f;
	}

	return static_cast<int>(std::ceil(result));
}

int Text::GetHalfWidth() const
{
	int width = this->GetWidth();
	if (width > 0) {
		return width / 2;
	}

	return 0;
}

int Text::GetSize() const
{
	return _size;
}

const glm::ivec2& Text::GetPosition() const
{
	return _position;
}

const glm::vec4& Text::GetColor() const
{
	return _color;
}

const std::string& Text::GetText() const
{
	return _text;
}
