#include "Fireworks.h"



/*******************
*** class FlareSegment ***
********************/

FlareSegment::FlareSegment(sf::Vector2f pos, float radius, const sf::Color& color) :_radius(radius), _color(color) {
	_figure.setPosition(pos);
	_figure.setFillColor(_color);
	apply();
}

void FlareSegment::apply() {
	if (_radius > 0.01) {
		_figure.setRadius(_radius);
	}
	else
		_radius = 0;
}

void FlareSegment::changeRadius(float Dtime) {
	_radius -= _radius * QR *1.2* Dtime ;
	apply();
}

/*******************
*** class Flare ***
********************/

Flare::Flare(double Ux, double Uy,Fireworks* parent) :_Ux(Ux), _Uy(Uy) {
	_parent = parent;
	setColor(_parent->getCollor());
	_position = _parent->getPosition()*1.0;
	_radius = SUPPORT.getRandomNumber(4, 9);
	_circles.emplace_back(_position, _radius, _color);
}

void Flare::setColor(uint8_t col) {
	switch (colors(col)) {
	case (colors::RED):
		_color = sf::Color::Red;
		break;
	case (colors::GREEN):
		_color = sf::Color::Green;
		break;
	case (colors::BLUE):
		_color = sf::Color::Blue;
		break;
	case (colors::YELLOW):
		_color = sf::Color::Yellow;
		break;
	case (colors::MAGENTA):
		_color = sf::Color::Magenta;
		break;
	case (colors::CYAN):
		_color = sf::Color::Cyan;
		break;
	case(colors::PURPLE):
		_color = sf::Color::Color(227,71,204);
		break;
	case(colors::LITE_GREEN):
		_color = sf::Color::Color(143, 255, 107);
		break;
	case(colors::TURQUOISE):
		_color = sf::Color::Color(90, 224, 222);
		break;
	case(colors::DARK_BLUE):
		_color = sf::Color::Color(35, 22, 224);
		break;
	case(colors::ORANGE):
		_color = sf::Color::Color(248, 112, 58);
		break;
	default:
		_color = sf::Color::White;
	}
}

void Flare::changeFigure(float Dtime) {
	_radius -= _radius* QR *Dtime;
	if (_circles.size() > FLARE_TAIL)
		_circles.pop_back();

	for (auto &it : _circles) {
		it.changeRadius(Dtime);
	}
	_circles.emplace_front(_position, _radius, _color);
}

void Flare::move(float Dtime) {
	_Uy += g *2* QG *Dtime;
	if(_radius>=0.5){
		_position.x += _Ux * QU * Dtime;
		_position.y += _Uy * QU * Dtime;
		changeFigure(Dtime);
	}
	else {
		_radius = 0;
		changeFigure(Dtime);
	}
}


/*******************
*** class Fireworks ***
********************/

Fireworks::Fireworks(bool _randPos, bool plain) :_plain(plain) {
	_startPosition.x = SUPPORT.getRandomNumber(0, 1280);
	_startPosition.y = SUPPORT.getRandomNumber(0, 720);
	_color = SUPPORT.getRandomNumber(SUPPORT.getColorQty());
	createFlares();
}

Fireworks::Fireworks(sf::Vector2i pos, bool plain) :_plain(plain), _startPosition(pos) {
	_color = SUPPORT.getRandomNumber(SUPPORT.getColorQty());
	createFlares();
}

uint8_t Fireworks::getCollor() {
	if (_plain)
		return _color;
	return SUPPORT.getRandomNumber(SUPPORT.getColorQty());
}

void Fireworks::move(float Dtime) {
	for (auto& it : _flares)
		it->move(Dtime);
}

bool Fireworks::tryDone() {
	bool allready = std::all_of(_flares.begin(), _flares.end(), [](Flare* f) {
		return f->getRadius() == 0;
		});

	if (allready) {
		for (auto& it : _flares) {
			delete(it);
		}
		_flares.clear();
		return true;
	}
	return false;
}

void Fireworks::createFlares() {
	auto qty = SUPPORT.getRandomNumber(FLARE_QTY-3, FLARE_QTY+3);
	for (uint8_t i = 0; i < qty; i++) {
		auto first = SUPPORT.getRandomNumber(-_flareSize, _flareSize);
		auto second = SUPPORT.getRandomNumber(-_flareSize - 2, _flareSize - 5);
		Flare* a = new Flare(first, second, this);
		_flares.push_back(a);
	}
}

/*******************
*** class FireworksManager ***
********************/

void FireworksManager::draw() {
	std::for_each(_fireworks.begin(), _fireworks.end(), [this](Fireworks& f) {
		for (auto& it : f.getFlares())
			for (auto& itj : it->getFigures())
				_window->draw(itj.getFigure());
		});

}

bool FireworksManager::tryPopFront() {
	auto front = _fireworks.front();
	if (front.tryDone()) {
		_fireworks.pop_front();
		return true;
	}
	return false;
}

void FireworksManager::updateFireworks() {
	for (auto it : _fireworks) {
		if (!tryPopFront())
			break;
	}
}

void FireworksManager::move(float time) {
	std::for_each(_fireworks.begin(), _fireworks.end(), [time](Fireworks& f) {
		f.move(time);
		});
}

void FireworksManager::addFirework(sf::Vector2i vec, bool plain) {
	_fireworks.emplace_back(vec, plain);
}






