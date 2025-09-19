// creating a pong game

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace std;
int main(){
    // creating window
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Pong");
    window.setFramerateLimit(120);
    bool Over = false;

    sf::Clock clock;
    // creating a circle
    sf::CircleShape ball;
    ball.setRadius(20);
    ball.setPosition(930, 668);
    ball.setFillColor(sf::Color::Red);

    // creating two rectangles
    sf::RectangleShape p1; // player 1
    p1.setSize(sf::Vector2f(30, 120));
    p1.setPosition(2, 2);
    p1.setFillColor(sf::Color::Blue);
    
    sf::RectangleShape p2; // player 2
    p2.setSize(sf::Vector2f(30, 120));
    p2.setPosition(968, 678);
    p2.setFillColor(sf::Color::Magenta);

    // p1 and p2 can move up and down
    sf::Vector2f movement1(0, 0.0f); // to control p1's movement
    sf::Vector2f movement2(0, 0.0f); // to control p2's movement

    // circle can travel in both x and y direction
    // and it's speed depends on the way it is hit
    float moveX = 500.0;
    float moveY = 500.0;

    sf::Font font;
    font.loadFromFile("FreeRoyalty.ttf");
    sf::Text gameover;
    gameover.setFont(font);
    gameover.setCharacterSize(60);
    gameover.setPosition(300, 350);
    gameover.setFillColor(sf::Color::Red);

    while(window.isOpen()){
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        // forming click-listeners for p2
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Over == false){ // up and down is for p2
            movement2.y = -400.0; // as we're going up.. y decreases
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Over == false){
            movement2.y = 400.0;
        }
        else movement2.y = 0.0;


        // forming click-listeners for p1 (s and w)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && Over == false){ // w is for up
            movement1.y = -400.0;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Over == false){ // s is for down
            movement1.y = 400.0;
        }
        else movement1.y = 0.0;

        p1.move(movement1*deltaTime);
        p2.move(movement2*deltaTime);
        ball.move(moveX*deltaTime, moveY*deltaTime);

        // controlling p1
        if(p1.getPosition().y < 2){ 
            p1.setPosition(p1.getPosition().x, 2);
            movement1.y = -movement1.y;

        }
        else if(p1.getPosition().y > 678){
            p1.setPosition(p1.getPosition().x, 678);
            movement1.y = -movement1.y;
        }

        // controlling p2
        if(p2.getPosition().y > 678){
            p2.setPosition(p2.getPosition().x, 678);
            movement2.y = -movement2.y;
        }
        else if(p2.getPosition().y < 2){
            p2.setPosition(p2.getPosition().x, 2);
            movement2.y = -movement2.y;
        }

        // controlling ball
        // ball will move in both x and y axis...
        if(ball.getPosition().y > 761){
            ball.setPosition(ball.getPosition().x, 760);
            moveY = -moveY;
        }
        else if(ball.getPosition().y < 3){
            ball.setPosition(ball.getPosition().x, 2);
            moveY = -moveY;
        }
        else if(ball.getPosition().x >930){  
            if(ball.getGlobalBounds().intersects(p2.getGlobalBounds())){
                ball.setPosition(930, ball.getPosition().y);

                // calculate offset (how far from paddle center the ball hit)
                float ballCenterY = ball.getPosition().y + ball.getRadius();
                float paddleCenterY = p2.getPosition().y + p2.getSize().y / 2.0f;
                float offset = (ballCenterY - paddleCenterY) / (p2.getSize().y / 2.0f); // -1 (top), 0 (middle), +1 (bottom)

                // base speed
                float speed = sqrt(moveX*moveX + moveY*moveY);
                speed *= 1.1f;
                // bounce back to left
                moveX = -speed * cos(offset * 0.7f);  // mostly horizontal, angle changes with offset
                moveY = speed * sin(offset * 0.7f);   // vertical component depends on hit point
            }
            else{
                if(ball.getPosition().x > 960){
                    gameover.setString("Game Over!\nPlayer1 Wins");
                    Over = true;
                    ball.setPosition(960, ball.getPosition().y);
                    moveX = moveY = 0;
                }
            }
        }
        else if(ball.getPosition().x < 30){
            if(ball.getGlobalBounds().intersects(p1.getGlobalBounds())){
                ball.setPosition(30, ball.getPosition().y);

                float ballCenterY = ball.getPosition().y + ball.getRadius();
                float paddleCenterY = p1.getPosition().y + p1.getSize().y / 2.0f;
                float offset = (ballCenterY - paddleCenterY) / (p1.getSize().y / 2.0f);

                float speed = sqrt(moveX*moveX + moveY*moveY);

                // bounce back to right
                moveX = speed * cos(offset * 0.7f);
                moveY = speed * sin(offset * 0.7f);
            }
            else{
                if(ball.getPosition().x < 0){
                    gameover.setString("Game Over!\nPlayer2 Wins");
                    Over = true;
                    ball.setPosition(1, ball.getPosition().y);
                    moveX = moveY = 0;
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.draw(p1);
        window.draw(p2);
        window.draw(gameover);
        window.display();
    }
}
