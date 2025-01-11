#include "Renderer.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
{
	PrepareShaders();
	PrepareBuffers();
}

Renderer::~Renderer()
{
	// De-allocate all resources
	glDeleteProgram(_shaderProgram);
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}

Renderer& Renderer::GetInstance()
{
	static Renderer instance;
	return instance;
}

void Renderer::SetCamera(Camera* camera)
{
	_camera = camera;
}

void Renderer::DrawSprite(const Sprite* sprite) const
{
	/* Включаем смешивание цветов */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	{
		glUseProgram(_shaderProgram);
		glUniformMatrix4fv(_uProjectionLocation, 1, GL_FALSE, glm::value_ptr(_camera->GetTopLeftProjection()));

		glm::mat4 transform = sprite->GetMatrix();
		glUniformMatrix4fv(_uTransformLocation, 1, GL_FALSE, glm::value_ptr(transform));

		sprite->GetTexture()->Bind();
		glBindVertexArray(_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	glDisable(GL_BLEND);
}

void Renderer::DrawText(const Text& text)
{
	auto& font = text.GetFont();
	if (!font || !font->IsLoaded()) {
		return;
	}

	/* Отключаем тест глубины (чтобы шрифт печатался поверх сцены в любом случае) */
	glDisable(GL_DEPTH_TEST);

	/* Отключаем запись в маску глубины (потому что нас больше не волнует, что будет в буфере глубины - шрифт печатается после того, как сцена будет отрисована) */
	glDepthMask(0);

	/* Включаем смешивание цветов */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(font->_shader.ProgramId());
	glUniform4fv(font->_colorUniformLocation, 1, glm::value_ptr(text.GetColor()));
	glUniformMatrix4fv(font->_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(_camera->GetBottomLeftProjection()));

	int lastBoundTextureIndex = -1;

	const auto& position = text.GetPosition();
	glm::vec2 currentPos(position);

	/* Коэффициент соотношения размера пикселя, который нужно отрисовать, по отношению к размеру пикселя, с которым был загружен шрифт. */
	const float scale = float(text.GetSize()) / float(font->GetSize());

	glBindVertexArray(font->_vao);
	for (const auto& c : text.GetText()) {

		/* Если символ является новой строкой, то мы перемещаем нашу переменную позиции в начало следующей строки */
		if (c == '\n' || c == '\r') {
			currentPos.x = static_cast<float>(position.x);
			currentPos.y -= static_cast<float>(text.GetSize());
			continue;
		}

		/* Если нам неизвестен этот символ, пропускаем его */
		if (!font->HasChar(c)) {
			continue;
		}

		/* Если это не -1, то это то, что мы должны отобразить */
		const auto& props = font->GetProperties(c);
		if (props.renderIndex != -1) {
			if (lastBoundTextureIndex != props.textureIndex) {
				lastBoundTextureIndex = props.textureIndex;
				font->_textures.at(props.textureIndex)->Bind();
			}

			/* Матрица трансформации символа */
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(currentPos.x, currentPos.y, 0.0f));
			model = glm::scale(model, glm::vec3(scale, scale, 1.0f));

			glUniformMatrix4fv(font->_modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLE_STRIP, props.renderIndex, 4);
		}

		/* В конце рендеринга каждого символа мы изменяем наше горизонтальное положение, используя метрику FreeType AdvanceX. */
		currentPos.x += props.advanceX * scale;
	}

	/* Восстанавливаем старое состояние — отключаем смешивание и снова включаем тест глубины и запись в буфер глубины. */
	glDisable(GL_BLEND);
	glDepthMask(1);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::PrepareShaders()
{
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"uniform mat4 uTransform;\n"
		"uniform mat4 uProjectionLocation;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = uProjectionLocation * uTransform * vec4(aPos, 1.0);\n"
			"TexCoord = aTexCoord;\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform sampler2D uTexture;\n"
		"in vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(uTexture, TexCoord);\n"
		"}\n\0";

	// Vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// Create shader program
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	// De-allocate shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	_uColorLocation = glGetUniformLocation(_shaderProgram, "uColor");
	_uTransformLocation = glGetUniformLocation(_shaderProgram, "uTransform");
	_uProjectionLocation = glGetUniformLocation(_shaderProgram, "uProjectionLocation");
}

void Renderer::PrepareBuffers()
{
	//const float vertices[] = {
	//	// positions        // texture coords
	//	0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
	//	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
	//};

	const float vertices[] = {
		0.0f, 0.0f, 0.0f,  1.0f, 1.0f, // Левый верхний 
		1.0f, 0.0f, 0.0f,  1.0f, 0.0f, // Правый верхний
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Правый нижний
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Левый нижний
	};

	// note that we start from 0!
	const unsigned int indices[] = {

		0, 1, 3, // first triangle
		1, 2, 3, // second triangle
	};

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);
	glBindVertexArray(_VAO);

	// Send the vertex array to a video card memory
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Send the indices array to a video card memory
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Texture coords attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
