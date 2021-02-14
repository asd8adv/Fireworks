#include "Support.h"

/*******************
*** class Support ***
********************/
Support::Support() {
	std::random_device rd;
	_rands = std::mt19937(rd());
}

int32_t Support::getRandomNumber(int32_t lower, int32_t upper) {
	auto num = _rands();
	if (upper != 0) {
		if (lower > upper) {
			return 0;
		}
		auto diff = upper - lower;
		return lower + num % (diff + 1);
	}
	else {
		return num % (lower + 1);
	}
}

/*******************
*** class MessageManager ***
********************/

MessageManager::MessageManager(std::shared_ptr<sf::RenderWindow> window) :_window(window) {
	font.loadFromFile("Resources/raleway.ttf");

	_fps = std::make_unique<sf::Text>( std::move(sf::Text("-", font, 20)));
	_fps->setStyle(sf::Text::Bold);
	_fps->setPosition(10, 10);

	_fire = std::make_unique<sf::Text>(std::move(sf::Text("-", font, 20)));
	_fire->setStyle(sf::Text::Bold);
	_fire->setPosition(10, 30);
}

void MessageManager::messageChange(MessageType mes, const std::string& newValue) {
	std::string result;
	switch (mes)
	{
	case MessageType::FPS:
		result = "FPS : ";
		result += newValue;
		_fps->setString(result);
		break;
	case MessageType::FIREWORKS:
		result = "fireworks count : ";
		result += newValue;
		_fire->setString(result);
		break;
	default:
		break;
	}
}

void MessageManager::draw() {
	_window->draw(*_fps);
	_window->draw(*_fire);
}
