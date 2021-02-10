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

MessageManager::MessageManager(sf::RenderWindow& window) :_window(&window) {
	font.loadFromFile("Resources/raleway.ttf");

	_FPS = new sf::Text("-", font, 20);
	_FPS->setStyle(sf::Text::Bold);
	_FPS->setPosition(10, 10);

	_FIRE = new sf::Text("-", font, 20);
	_FIRE->setStyle(sf::Text::Bold);
	_FIRE->setPosition(10, 30);
}

void MessageManager::messageChange(MessageType mes, const std::string& newValue) {
	std::string result;
	switch (mes)
	{
	case MessageType::FPS:
		result = "FPS : ";
		result += newValue;
		_FPS->setString(result);
		break;
	case MessageType::FIREWORKS:
		result = "fireworks count : ";
		result += newValue;
		_FIRE->setString(result);
		break;
	default:
		break;
	}
}

void MessageManager::draw() {
	_window->draw(*_FPS);
	_window->draw(*_FIRE);
}
