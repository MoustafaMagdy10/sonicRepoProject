
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Network.hpp>

using namespace std;
using namespace sf;
void Movement(Sprite& sonic, int& x, int& y, View& camera, Sprite& gd);
int main()
{
    int x = 0, y = 0, velocityY = 3;
    RenderWindow window(sf::VideoMode(1022, 498), "Sonic");
    window.setFramerateLimit(30);
    Texture background, player, ground , bullet;
    background.loadFromFile("SonicLevel2.png");
    bullet.loadFromFile("bullet.png");
    ground.loadFromFile("Backgroung_ground.png");
    player.loadFromFile("sonicModified.png");


    RectangleShape rect;
    rect.setSize(Vector2f(3, 10));
    rect.setPosition(0, 15);


    Sprite back, sonic, gd,bt;
    back.setTexture(background);
    back.setPosition(0, 0);
    gd.setTexture(ground);
    gd.setPosition(0, 240);
    sonic.setTexture(player);
    sonic.setPosition(0, 30);
    sonic.setTextureRect(IntRect(x * 80, y * 100, 80, 100));
    sonic.setOrigin(42, 51);
    sonic.scale(0.5, 0.5);
    bt.setTexture(bullet);
    bt.scale(0.01, 0.01);
 /*   View camera(FloatRect(0, 0, 10, 80));*/
   
    /*  camera.setCenter(sonic.getPosition());*/
   /* window.setView(camera);*/

    bool flag=false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
      
       /* sonic.move(0, 10)*/
        if ((Keyboard::isKeyPressed(Keyboard::Key::Space)) )
        {
            bt.setPosition(sonic.getPosition());
            window.draw(bt);
            while (bt.getPosition().x>0)
            {
                bt.move(1, 0);
                
            }
            window.clear();
           
            
           
            
           
        }
   /*     if ((Keyboard::isKeyPressed(Keyboard::Key::W)) || (Keyboard::isKeyPressed(Keyboard::Key::Up)))
        {
            
            sonic.move(0, -10);

        }*/

        if ((Keyboard::isKeyPressed(Keyboard::Key::S)) || (Keyboard::isKeyPressed(Keyboard::Key::Down)))
        {
            y = 2;
            x = 0;
            sonic.setTextureRect(IntRect(x * 84, y * 103, 84, 103));

        }
        if ((Keyboard::isKeyPressed(Keyboard::Key::D)) || (Keyboard::isKeyPressed(Keyboard::Key::Right)))

        {
            sonic.setScale(0.5, 0.5);
            x++;
            if (x % 9 == 0) {

                y = 1;
            }
            if (x == 3 && y == 1) {
                y = 0;
            }

            sonic.move(10, 0);
           /* camera.move(10, 0);*/



            x %= 9;
            sonic.setTextureRect(IntRect(x * 84, y * 103, 84, 103));
        }
        else if ((Keyboard::isKeyPressed(Keyboard::Key::A)) || (Keyboard::isKeyPressed(Keyboard::Key::Left)))
        {
            sonic.setScale(-0.5, 0.5);
            x++;
            if (x % 9 == 0) {

                y = 1;
            }
            if (x == 3 && y == 1) {
                y = 0;
            }
            sonic.move(-10, 0);
          /*  camera.move(-10, 0);*/

            x %= 9;
            sonic.setTextureRect(IntRect(x * 84, y * 103, 84, 103));
        }






      /*  window.setView(camera);*/
        window.clear();
        /*  window.draw(back);*/
        window.draw(sonic);
        window.draw(rect);
        window.draw(bt);
        //window.draw(gd);
        window.display();

    }
}


//void Movement(Sprite& sonic, int& x, int& y ,View& camera, Sprite& gd,int) {
//  
//}




/*          
Sonic

void SonicMovement(Sprite &sonic,int &x,int &y);
void SonicJump(Sprite& sonic, int& x, int& y , RectangleShape &ground);
void collision_Coin(Sprite& sonic, Sprite Coin[10], int &score , Text &text);
void Coin_Animation(Sprite Coin[10], int& x2, int& y2);


int main() {

    
    RenderWindow window(VideoMode(1022, 498), "SFML works!");
    window.setFramerateLimit(30);

    int x = 0, y = 0, x2 = 0, y2 = 0, score = 0;



    RectangleShape rect, ground;
    ground.setSize(Vector2f(1022, 50));
    ground.setPosition(0, 400);
    rect.setSize(Vector2f(1022, 70));

    Texture sonictexture, backgroundtexture, cointexture;
    cointexture.loadFromFile("SonicCoinsAnimation.png");
    sonictexture.loadFromFile("SonicAnimation copy.png");
    backgroundtexture.loadFromFile("SonicBackground.jpg");


    Sprite sonic, Back, Coin[10];
    Back.setTexture(backgroundtexture);
    sonic.setTexture(sonictexture);
    sonic.setPosition(42, 350);
    sonic.setTextureRect(IntRect(x * 84, y * 103, 84, 103));
    sonic.setOrigin(42, 51);

    for (int i = 0; i < 10; i++)
    {
        Coin[i].setTexture(cointexture);
        Coin[i].setPosition(200 + (i * 50), 340);
        Coin[i].setScale(0.3, 0.3);
        Coin[i].setTextureRect(IntRect(x2 * 135, y2 * 134, 135, 134));
    }

    Font font;
    font.loadFromFile("Asman.ttf");


    Text text;
    text.setFont(font);
    text.setString("Score : " + to_string(score));
    text.setPosition(10, 10);
    text.setFillColor(Color(50, 200, 300, 200));
    text.setCharacterSize(50);

    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        SonicJump(sonic, x, y , ground);

        SonicMovement(sonic , x, y);

        collision_Coin(sonic, Coin, score, text);
        
        Coin_Animation(Coin, x2, y2);
        
         

        window.clear();
        window.draw(Back);
        window.draw(rect);
        window.draw(text);
        window.draw(sonic);
        for (size_t i = 0; i < 10; i++)
        {
            window.draw(Coin[i]);

        }

        
        window.display();
    }


    return 0;
}






void SonicMovement(Sprite &sonic , int &x ,int &y) {
    if (Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        y = 2;
        x = 0;
        sonic.setTextureRect(IntRect(x * 84, y * 103, 84, 103));

    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::D))
    {
        sonic.setScale(1, 1);
        x++;
        if (x % 9 == 0) {

            y = 1;
        }
        if (x == 3 && y == 1) {
            y = 0;
        }
        sonic.move(15, 0);
        x %= 9;

        sonic.setTextureRect(IntRect(x * 84, y * 103, 84, 103));
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
        sonic.setScale(-1, 1);
        x++;
        if (x % 9 == 0) {

            y = 1;
        }
        if (x == 3 && y == 1) {
            y = 0;
        }
        sonic.move(-15, 0);
        x %= 9;
        sonic.setTextureRect(IntRect(x * 84, y * 103, 84, 103));
    }
}

void SonicJump(Sprite& sonic, int& x, int& y ,RectangleShape &ground) {
    if (sonic.getGlobalBounds().intersects(ground.getGlobalBounds())) {

        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            for (int i = 1; i < 15; i++)
            {
                sonic.move(0, -i);
            }

        }
    }
    else {

        sonic.move(0, 7);
        y = 2;
        x = 0;
        sonic.setTextureRect(IntRect(x * 84, y * 103, 84, 103));
    }
}

void collision_Coin(Sprite& sonic, Sprite Coin[10], int &score , Text &text) {
    for (int i = 0; i < 10; i++)
    {
        if (sonic.getGlobalBounds().intersects(Coin[i].getGlobalBounds()))
        {
            score++;
            Coin[i].setScale(0, 0);
            text.setString("Score : " + to_string(score));
        }
    }
}

void Coin_Animation(Sprite Coin[10], int& x2, int& y2) {

    x2++;
    x2 %= 10;
    for (int i = 0; i < 10; i++)
    {

        Coin[i].setTextureRect(IntRect(x2 * 135, y2 * 134, 135, 134));
    }

}
*/