
#include"Fireworks.h"






int main()
{



	sf::Image bgImage;
	bgImage.loadFromFile("Resources/bg.jpg");	
	sf::Texture bgTX;
	bgTX.loadFromImage(bgImage);
	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTX);

	sf::RenderWindow window(sf::VideoMode(1280,720), "fireworks");
	FireworksManager fireworks(window);
	MessageManager messages(window);

	sf::Clock clock;
	sf::Clock clockForUpdate;

	int FPSQty = 0;
	int fireQty = 0;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		float timeForUpdate = clockForUpdate.getElapsedTime().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {	window.close();	}


		if (event.type == sf::Event::MouseButtonReleased){
			fireQty++;
			std::string fireValue = std::to_string(fireQty);
			messages.messageChange(MessageManager::MessageType::FIREWORKS, fireValue);
			if (event.key.code == sf::Mouse::Left) {
				fireworks.addFirework(sf::Mouse::getPosition(window));
			}
			else
				fireworks.addFirework(sf::Mouse::getPosition(window),true);
			event.type = sf::Event::MouseWheelMoved;
		}


		//std::cout << ff.getFigure().getPosition().x << " " << ff.getFigure().getPosition().y<<"\n";
		if (time > 0.01f) {
			fireworks.move(time);
			clock.restart();
			window.clear();
		}

			
		window.draw(bgSprite);
		messages.draw();
		fireworks.draw();
		window.display();
		FPSQty++;
		if (timeForUpdate >= 1.0f) {//update FireworksManager each second
			fireworks.updateFireworks();
			
			std::string fpsValue = std::to_string(FPSQty);
			messages.messageChange(MessageManager::MessageType::FPS, fpsValue);
			FPSQty = 0;
			clockForUpdate.restart();
		}
		
	


	}

	return 0;
}