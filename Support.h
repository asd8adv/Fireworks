#include <SFML/Graphics.hpp>
#include <random>


enum class colors :uint8_t {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	CYAN,
	PURPLE,
	LITE_GREEN,
	TURQUOISE,
	DARK_BLUE,
	ORANGE
};

class Support {
	std::mt19937 _rands;
public:
	Support();

	uint8_t getColorQty()const { return uint8_t(colors::ORANGE)+1; }
	int32_t getRandomNumber(int32_t lower, int32_t upper = 0);
};


class MessageManager {
	sf::RenderWindow* _window;
	sf::Text* _FPS;
	sf::Text* _FIRE;
	sf::Font font;
public:
	enum class MessageType :uint8_t {
		FPS,
		FIREWORKS
	};
	MessageManager(sf::RenderWindow& window);

	void messageChange(MessageType mes, const std::string& newValue);

	void draw();

};