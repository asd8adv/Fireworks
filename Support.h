#include <SFML/Graphics.hpp>
#include <random>
#include <memory>



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
	std::shared_ptr<sf::RenderWindow> _window;
	std::unique_ptr<sf::Text> _fps;
	std::unique_ptr<sf::Text> _fire;
	sf::Font font;
public:
	enum class MessageType :uint8_t {
		FPS,
		FIREWORKS
	};
public:
	MessageManager(std::shared_ptr<sf::RenderWindow> window);

	void messageChange(MessageType mes, const std::string& newValue);

	void draw();

};