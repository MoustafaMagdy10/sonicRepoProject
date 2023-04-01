
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Network.hpp>

using namespace std;
using namespace sf;

/*<!-- functions -->*/
void background();
void movement(struct Mainplayer);
void coins();
void menue();
void gameLoad();	
void ground(Sprite grounds[]);


struct Mainplayer
{
	Sprite sonic;
	float currentframe;
	float  move_Y, move_X;
	bool onground;
	FloatRect rect;

		// Sonic Set
		void sp(Texture& player)   
		{
		sonic.setTexture(player);
		sonic.setTextureRect(IntRect(0, 0, 84, 103));
		sonic.setScale(1.1, 1.1);
		move_X = 0;
		move_Y = 0;
		currentframe = 0;	
		}	
		// Sonic update at every frame
		void update(float time) {
			rect.left += move_X * time;   // sonic movement at x set
			rect.top += move_Y * time;   // sonic movement at y set
			onground = false;
			if (!onground) 
			{
				move_Y += (0.005 * time);   // Gravity
			}
			currentframe += 0.05 * time;
			if (currentframe > 6) {
				currentframe -= 6;
			}
			if (move_X > 0) {
				sonic.setTextureRect(IntRect(84 * int(currentframe), 0, 84, 103));    // sonic changing to next frame pic
			}
			if (move_X < 0) {
				sonic.setTextureRect(IntRect(84 * int(currentframe)+84, 0, -84, 103));  // sonic changing to next frame pic by opposite dir
			}
			sonic.setPosition(rect.left, rect.top);  // sonic real movement 
			move_X = 0;
		}
		

};



long long x = 0, y = 0, lastKeyPressed;  //variables

int main()
{
	// window
	RenderWindow window(VideoMode(800, 480), "Sonic", Style::Default);
	window.setFramerateLimit(30);

	// sonic texture
	Texture player; 
	player.loadFromFile("sonicModified.png");
	



	//MAP
	Texture background, map;
	background.loadFromFile("map.png");
	map.loadFromFile("map.png");
	Sprite back, grounds[13];
	back.setTexture(background);
	for (int i = 0; i < 13; i++) {
		grounds[i].setTexture(map);
	}


	//clock for time
	Clock clock;


    //Sonic call from struct
	Mainplayer Sonic;
	Sonic.sp(player);
	Sonic.rect.left = 56;
	Sonic.rect.top = 300;

	// window camera
	View camera;
	camera.setCenter(Sonic.sonic.getPosition().x + 500, Sonic.sonic.getPosition().y);
	window.setView(camera);




	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		// time
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 650;
		if (time>20)
		{
			time = 20;
		}


		// lastkeypressed variable to know which side to draw sonic at static state
		if (lastKeyPressed == 1)
		{
			Sonic.sonic.setTextureRect(IntRect(0, 0, 80, 100));
		}
		else 
		{
			Sonic.sonic.setTextureRect(IntRect(0+80, 0, -80, 100));
		}


		//set the map
		ground(grounds);
		

		// to know any pos at the window by left click
		if ((Mouse::isButtonPressed(Mouse::Left)))
		{
			Vector2i mousepos = Mouse::getPosition(window);
			cout << mousepos.x << " " << mousepos.y<<endl;

		}

		// jump
		if ((Keyboard::isKeyPressed(Keyboard::Key::W)) || (Keyboard::isKeyPressed(Keyboard::Key::Up)))
		{
			
			
				Sonic.move_Y = -0.4;
				Sonic.onground = false;
			


		}
		// moving right
		if ((Keyboard::isKeyPressed(Keyboard::Key::D)) || (Keyboard::isKeyPressed(Keyboard::Key::Right)))
		{
			Sonic.move_X = 0.75;
			lastKeyPressed = 1;
			camera.move(15,0);
			
		}
		// moving left
		else if ((Keyboard::isKeyPressed(Keyboard::Key::A)) || (Keyboard::isKeyPressed(Keyboard::Key::Left)))
		{
			Sonic.move_X = -0.75;
			lastKeyPressed = -1;
			camera.move(-15, 0);

		}


		// collistion
		for (int i = 0; i < 13; i++) {
			if (Sonic.sonic.getGlobalBounds().intersects(grounds[i].getGlobalBounds())  && (Sonic.rect.left < grounds[i].getPosition().x + 470)) {
				Sonic.onground = true;
				Sonic.rect.top = grounds[i].getPosition().y - 100;
				Sonic.move_Y = 0;
				if (i==1 || i==3 || i == 8 || i==6)
				{
					return 0;
				}
			}
		}


		window.setView(camera);  //window view
		Sonic.update(time);   // all sonic actions
		window.clear();   // renew window
		//draw the map
		for (int i = 0; i < 13; i++)
		{
			window.draw(grounds[i]);
		}
		window.draw(Sonic.sonic); //sonic draw
		window.display();

	}
}

void ground(Sprite grounds[]) {
	grounds[0].setTextureRect(IntRect(0, 384, 513, 96));
	grounds[0].setPosition(0, 384);
	grounds[1].setTextureRect(IntRect(513, 414, 190, 66)); //trap
	grounds[1].setPosition(513, 414);
	grounds[2].setTextureRect(IntRect(704, 384, 160, 96));
	grounds[2].setPosition(704, 384);
	grounds[3].setTextureRect(IntRect(866, 414, 190, 66)); //trap
	grounds[3].setPosition(866, 414);
	grounds[4].setTextureRect(IntRect(1056, 384, 478, 96));
	grounds[4].setPosition(1056, 384);
	grounds[5].setTextureRect(IntRect(1536, 224, 160, 256));
	grounds[5].setPosition(1536, 224);
	grounds[6].setTextureRect(IntRect(1697, 253, 703, 227));
	grounds[6].setPosition(1697, 253);//trap
	grounds[7].setTextureRect(IntRect(2400, 224, 321, 256));
	grounds[7].setPosition(2400, 224);
	grounds[8].setTextureRect(IntRect(2721, 445, 670, 35)); //trap
	grounds[8].setPosition(2721, 445);
	grounds[9].setTextureRect(IntRect(2816, 159, 96, 33));
	grounds[9].setPosition(2816, 159);
	grounds[10].setTextureRect(IntRect(3008, 224, 96, 33));
	grounds[10].setPosition(3008, 224);
	grounds[11].setTextureRect(IntRect(3167, 352, 96, 33));
	grounds[11].setPosition(3167, 352);
	grounds[12].setTextureRect(IntRect(3392, 384, 1375, 96));
	grounds[12].setPosition(3392, 384);
	grounds[13].setTextureRect(IntRect(4767, 0, 33, 480));
	grounds[13].setPosition(4767, 0);


}