#include "Font.h"

// Зависимости
#include <glad/glad.h>
#include <glm/glm.hpp> 

// STL
#include <iostream> 

/* Размер текстурного атласа */
const int Font::CHARACTERS_TEXTURE_SIZE = 512;

Font::Font()
{
    /* Этот код будет вызван один раз. */
    /* Здесь создается шейдерная программа для отрисовки символов. */
    static std::once_flag prepareOnceFlag;
    std::call_once(prepareOnceFlag, [this]() {

        const std::string vertexShaderSource = R"(
            #version 330 core

	        uniform mat4 projMatrix;
	        uniform mat4 modelMatrix;

            layout(location = 0) in vec2 vertexPosition;
            layout(location = 1) in vec2 vertexTexCoord;

            smooth out vec2 ioVertexTexCoord;

            void main()
            {
	            mat4 mvpMatrix = projMatrix * modelMatrix;
	            gl_Position = mvpMatrix * vec4(vertexPosition, 0.0, 1.0);
	            ioVertexTexCoord = vertexTexCoord;
            }
        )";

        const std::string fragmentShaderSource = R"(
            #version 330 core

            layout(location = 0) out vec4 outputColor;

            smooth in vec2 ioVertexTexCoord;

            uniform sampler2D sampler;
            uniform vec4 color;

            void main()
            {
	            vec4 texel = texture(sampler, ioVertexTexCoord);
	            texel = vec4(texel.r, texel.r, texel.r, texel.r);
	            if(texel.a == 0.0) {
		            discard;
                }
	            outputColor = texel * color;
	        }
        )";

        _shader.AddShaderFromSourceCode(Shader::ShaderType::Vertex, vertexShaderSource);
        _shader.AddShaderFromSourceCode(Shader::ShaderType::Fragment, fragmentShaderSource);
        _shader.Create();

        _projectionMatrixLocation = _shader.AttributeLocation("projMatrix");
        _modelMatrixLocation = _shader.AttributeLocation("modelMatrix");
        _colorUniformLocation = _shader.AttributeLocation("color");
    });
}

std::shared_ptr<Font> Font::Create(const std::string& filename, int size)
{
    if (size < 1 || size > CHARACTERS_TEXTURE_SIZE) {

    }

    /* Создаём шрифт */
    auto font = std::make_shared<Font>();

    /* Загружаем данные шрифта в память */
    FT_Face face{ 0 };
    if (FT_New_Face(FontDevice::GetInstance().GetLibrary(), filename.c_str(), 0, &face)) {
        std::cout << "Error: FreeType failed to load font" << std::endl;
        return { 0 };
    }

    /* Устанавливаем размер пикселя загруженного шрифта */
    if (FT_Set_Pixel_Sizes(face, 0, size)) {
        std::cout << "Error: FreeType failed to setup pixel sizes" << std::endl;
    }
        
    /* Буфер для хранения данных текстуры */
    std::vector<unsigned char> textureData(CHARACTERS_TEXTURE_SIZE * CHARACTERS_TEXTURE_SIZE, 0);

    int currentPixelPositionRow = 0;
    int currentPixelPositionCol = 0;
    int currentRenderIndex = 0;
    int rowHeight = 0;

    /* Создаём текстуру */
    auto texture = std::make_unique<Texture>();

    /* Создаём VAO */
    glGenVertexArrays(1, &font->_vao);
    glBindVertexArray(font->_vao);

    /* Создаём VBO */
    glGenBuffers(1, &font->_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, font->_vbo);

    /* 
    * Сохраняем ссылку на буфер текстур.
    * Это нужно, чтобы из лямбды получить доступ к приватному полю.
    */
    auto textures = std::ref(font->_textures);

    /* Финализируем текстуру и инициализируем данные для другой, если это необходимо */
    auto finalizeTexture = [&textures, &font, & texture, & textureData](bool createNext) {
        texture->SetFormat(TextureFormat::DepthFormat);
        if (!texture->LoadFromData(textureData.data(), CHARACTERS_TEXTURE_SIZE, CHARACTERS_TEXTURE_SIZE)) {
            std::cout << "Error: Failed to load texture from data" << std::endl;
        }

        if (!texture->Create()) {
            std::cout << "Error: Failed to create texture" << std::endl;
        }

        textures.get().push_back(std::move(texture));
        
        if (createNext) {
            texture = std::make_unique<Texture>(); // Создаём следующую текстуру
            std::memset(textureData.data(), 0, textureData.size()); // Инициализируем буфер нулями
        }
    };

    std::vector<unsigned char> rawData_; // Буфер необработанных данных в памяти, используемый для сбора данных для VBO
    rawData_.reserve(1024);

    size_t bytesAdded_{ 0 };             // Количество байт, добавленных в буфер 

    // Добавляет необработанные данные в буфер в памяти перед их загрузкой.
    auto addRawData = [&rawData_, &bytesAdded_](const void* ptrData, size_t dataSizeBytes) {
        const auto bytesToAdd = dataSizeBytes;
        const auto requiredCapacity = bytesAdded_ + bytesToAdd;

        // Если текущей емкости недостаточно, изменим размер вектора
        if (requiredCapacity > rawData_.capacity())
        {
            // Определим объем нового буфера - увеличиваем его в два раза, пока он не станет достаточно большим
            auto newCapacity = rawData_.capacity() * 2;
            while (newCapacity < requiredCapacity) {
                newCapacity *= 2;
            }

            // Резервируем новый вектор с большей емкостью (который заменит элемент rawData_) и копируем существующие данные поверх
            std::vector<unsigned char> newRawData;
            newRawData.reserve(newCapacity);
            memcpy(newRawData.data(), rawData_.data(), bytesAdded_);
            rawData_ = std::move(newRawData);
        }

        // Добавляем данные
        memcpy(rawData_.data() + bytesAdded_, ptrData, dataSizeBytes);
        bytesAdded_ += dataSizeBytes;
    };

    /* Загружаем первые 128 символов ASCII набора */
    for (unsigned int code = 32; code <= 127;) {

        /* Загружаем символ во внутренние структуры FreeType */
        if (FT_Load_Glyph(face, FT_Get_Char_Index(face, code), FT_LOAD_DEFAULT)) {
            std::cout << "Error: FreeType failed to load ASCII glyph - " << code << std::endl;
        }

        /* Визуализируем символ в буфер памяти */
        if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL)) {
            std::cout << "Error: FreeType failed to render ASCII glyph - " << code << std::endl;
        }

        const auto& bitmap = face->glyph->bitmap;
        const int bitmapWidth = bitmap.width;
        const int bitmapHeight = bitmap.rows;
        const int rowsLeft = CHARACTERS_TEXTURE_SIZE - currentPixelPositionRow;
        const int colsLeft = CHARACTERS_TEXTURE_SIZE - currentPixelPositionCol;
    
        rowHeight = std::max(rowHeight, bitmapHeight);

        if (colsLeft < bitmapWidth) {
            currentPixelPositionCol = 0;
            currentPixelPositionRow += rowHeight + 1;
            rowHeight = 0;
            continue;
        }

        if (rowsLeft < bitmapHeight) {
            finalizeTexture(true);
            currentPixelPositionCol = 0;
            currentPixelPositionRow = 0;
            rowHeight = 0;
            continue;
        }

        /*  
        * По какой-то причине FreeType измеряет данные в 1/64 пикселя. 
        * Поэтому, чтобы получить фактические значения пикселей, нам нужно умножить числа, которые приходят из FreeType, 
        * на число 64 или выполнить правый двоичный сдвиг на 6, что делает то же самое, но должно быть немного быстрее. 
        */
        auto& charProps    = font->_characterProperties[code]; // Это также создает запись, если она не существует 
        charProps.code     = code;
        charProps.width    = face->glyph->metrics.width        >> 6;
        charProps.height   = face->glyph->metrics.height       >> 6;
        charProps.bearingX = face->glyph->metrics.horiBearingX >> 6;
        charProps.bearingY = face->glyph->metrics.horiBearingY >> 6;
        charProps.advanceX = face->glyph->metrics.horiAdvance  >> 6;

        /* Пропускаем символы, которые не поддаются визуализации, вроде символа пробела. */
        if (bitmapWidth == 0 && bitmapHeight == 0) {
            charProps.renderIndex = -1;
            charProps.textureIndex = -1;
            code++;
            continue;
        }

        /* Копируем отрисованные данные символа из FreeType в наш буфер данных текстуры, используя старую добрую функцию memcpy */
        for (int i = 0; i < bitmapHeight; ++i) {
            int globalRow = currentPixelPositionRow + i;
            int reversedRow = bitmapHeight - i - 1;
            std::memcpy(textureData.data() + globalRow * CHARACTERS_TEXTURE_SIZE + currentPixelPositionCol,
                bitmap.buffer + reversedRow * bitmapWidth, bitmapWidth);
        }

        /* 
        * Строим вершины небольшого квадрата из полосы треугольников, чтобы отрисовать один символ 
        * https://www.freetype.org/freetype2/docs/glyphs/glyphs-3.html
        */
        glm::vec2 vertices[] =
        {
            glm::vec2(static_cast<float>(charProps.bearingX), static_cast<float>(charProps.bearingY)),
            glm::vec2(static_cast<float>(charProps.bearingX), static_cast<float>(charProps.bearingY - charProps.height)),
            glm::vec2(static_cast<float>(bitmapWidth + charProps.bearingX), static_cast<float>(charProps.bearingY)),
            glm::vec2(static_cast<float>(bitmapWidth + charProps.bearingX), static_cast<float>(charProps.bearingY - charProps.height))
        };

        /* Используя текущую позицию в нашем атласе текстур и метрики текущего символа, генерируем координаты текстуры */
        glm::vec2 textureCoordinates[] =
        {
            glm::vec2(static_cast<float>(currentPixelPositionCol) / static_cast<float>(CHARACTERS_TEXTURE_SIZE), static_cast<float>(currentPixelPositionRow + bitmapHeight) / static_cast<float>(CHARACTERS_TEXTURE_SIZE)),
            glm::vec2(static_cast<float>(currentPixelPositionCol) / static_cast<float>(CHARACTERS_TEXTURE_SIZE), static_cast<float>(currentPixelPositionRow) / static_cast<float>(CHARACTERS_TEXTURE_SIZE)),
            glm::vec2(static_cast<float>(currentPixelPositionCol + bitmapWidth) / static_cast<float>(CHARACTERS_TEXTURE_SIZE), static_cast<float>(currentPixelPositionRow + bitmapHeight) / static_cast<float>(CHARACTERS_TEXTURE_SIZE)),
            glm::vec2(static_cast<float>(currentPixelPositionCol + bitmapWidth) / static_cast<float>(CHARACTERS_TEXTURE_SIZE), static_cast<float>(currentPixelPositionRow) / static_cast<float>(CHARACTERS_TEXTURE_SIZE))
        };

        /* Копируем данные в VBO */
        for (int i = 0; i < 4; ++i) {
            addRawData(&vertices[i], sizeof(glm::vec2));
            addRawData(&textureCoordinates[i], sizeof(glm::vec2));
        }

        /* 
        * Запоминаем индекс, где этот конкретный символ начинается в VBO. 
        * Это отслеживается с помощью переменной currentRenderIndex , которая в конце обновляется для каждого символа. 
        * Символ также помнит, в какой текстуре он хранится (может быть несколько атласов текстур, содержащих все символы).
        */
        charProps.renderIndex = currentRenderIndex;
        charProps.textureIndex = static_cast<int>(font->_textures.size());
        currentPixelPositionCol += bitmapWidth + 1;
        currentRenderIndex += 4;
        code++;
    }

    /* Добавляем последнюю текстуру, если она не пустая */
    if (currentPixelPositionRow > 0 || currentPixelPositionCol > 0) {
        finalizeTexture(false);
    }

    /* Загружаем данные в GPU */
    glBufferData(GL_ARRAY_BUFFER, bytesAdded_, rawData_.data(), GL_STATIC_DRAW);

    /* Настраиваем указатели вершин и сохраняем их в VAO */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) * 2, reinterpret_cast<void*>(0));

    /* Настраиваем указатели текстурных координат и сохраняем их в VAO */
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) * 2, reinterpret_cast<void*>(sizeof(glm::vec2)));

    /* Деинициализируем загруженный шрифт */
    if (FT_Done_Face(face)) {
        std::cout << "Error: FreeType failed to done face - " << filename << std::endl;
    }

    font->_size = size;
    font->_loaded = true;

    return font;
}

bool Font::HasChar(unsigned char c)
{
    bool result = _characterProperties.count(c) != 0;
    return result;
}

const Font::CharacterProperties& Font::GetProperties(unsigned char c) const
{
    return _characterProperties.at(c);
}

bool Font::IsLoaded() const
{
    return _loaded;
}

int Font::GetSize() const
{
    return _size;
}
