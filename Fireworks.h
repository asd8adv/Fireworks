#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <deque>
#include <iostream>
#include "Support.h"
class Fireworks; 
class Support;

inline constexpr auto g = 9.8;
inline constexpr auto QU = 1.3;
inline constexpr auto QR = 5;
inline constexpr auto QG = 6;
inline constexpr auto FLARE_TAIL = 12;
inline constexpr auto FLARE_QTY = 12;

static sf::Vector2f operator*(const sf::Vector2i& v, float f) {
	sf::Vector2f vec;
	vec.x = v.x * f;
	vec.y = v.y * f;
	return vec;
}

static Support SUPPORT;


struct FlareSegment {
	sf::Color _color;
	sf::CircleShape _figure;
	float _radius;

	FlareSegment(sf::Vector2f pos, float radius, const sf::Color& color);

	const sf::CircleShape& getFigure() const { return _figure; }

	void apply();
	void changeRadius(float Dtime);
};



class Flare {
	Fireworks* _parent;
	sf::Color _color;
	sf::Vector2f _position;
	std::deque<FlareSegment> _circles;
	float _radius;
	double _Ux;
	double _Uy;
public:
	Flare(double Ux, double Uy, Fireworks* parent);

	const std::deque<FlareSegment>& getFigures() { return _circles; }
	float getRadius() const { return _radius; }

	void move(float Dtime);
	void changeFigure(float Dtime);
protected:
	void setColor(uint8_t col);
};


class Fireworks {
	sf::Vector2i _startPosition;
	std::vector<Flare*> _flares;
	bool _plain;
	uint8_t _flareSize;
	uint8_t _color;
public:
	Fireworks(bool _randPos = true, bool plain = false);
	Fireworks(sf::Vector2i pos, bool plain);

	sf::Vector2i getPosition() const { return _startPosition; }
	const std::vector<Flare*>& getFlares() { return _flares; }
	bool isPlain() const{ return _plain; }
	uint8_t getCollor();
	
	void move(float Dtime);
	bool tryDone();
protected:
	void createFlares();
};


class FireworksManager {
	std::deque<Fireworks> _fireworks;
	sf::RenderWindow* _window;
public:
	FireworksManager(sf::RenderWindow& window):_window(&window) 
	{}
	
	void draw();
	bool tryPopFront();
	void updateFireworks();
	void move(float time);
	void addFirework(sf::Vector2i vec, bool plain = 0);
};

