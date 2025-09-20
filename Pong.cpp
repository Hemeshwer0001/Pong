// creating a pong game

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace std;

void p1Clicks(sf::Vector2f& movement1, bool& Over){
// p1 will be controlled using mouse
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && Over==false){ // left click == up
        movement1.y = -400.0;
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && Over == false){ // right click == down
        movement1.y = 400.0;
    }
    else movement1.y = 0.0;
}

void p2Clicks(sf::Vector2f& movement2, bool& Over){
// forming click-listeners for p2
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Over == false){ // up and down is for p2
        movement2.y = -400.0; // as we're going up.. y decreases
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Over == false){
        movement2.y = 400.0;
    }
    else movement2.y = 0.0;
}

void boundP1(sf::RectangleShape& p1){ // ensuring that p1 stays in bounds
    if(p1.getPosition().y < 2){ 
        p1.setPosition(p1.getPosition().x, 2);

    }
    else if(p1.getPosition().y > 678){
        p1.setPosition(p1.getPosition().x, 678);
    }
}

void boundP2(sf::RectangleShape& p2){ // ensuring that p2 stays in bounds
    if(p2.getPosition().y > 678){
        p2.setPosition(p2.getPosition().x, 678);
    }
    else if(p2.getPosition().y < 2){
        p2.setPosition(p2.getPosition().x, 2);
    }
}

void boundBallAndGameOver(sf::CircleShape& ball, sf::RectangleShape& p1, sf::RectangleShape& p2, sf::Text& gameover, float& moveX, float& moveY, bool& Over, int& score1, int& score2){ // ensuring that ball moves properly throught the game until GameOver
    float ballLeft = ball.getPosition().x;
    float ballRight = ball.getPosition().x + ball.getRadius() * 2;
    // controlling ball
    // ball will move in both x and y axis...
    if(ball.getPosition().y > 761){ // 761: radius of ball is 20.. so, 761 ensures that the ball hits the bottom of screen and bounces
        ball.setPosition(ball.getPosition().x, 760);
        moveY = -moveY;
    }
    else if(ball.getPosition().y < 1){ // 3: ensures that ball hit the top of the screen and bounces
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
            speed *= 1.02f;
            // bounce back to left
            moveX = -speed * cos(offset * 0.7f);  // mostly horizontal, angle changes with offset
            moveY = speed * sin(offset * 0.7f);   // vertical component depends on hit point
        }
        else{
            if(ballRight > 1000){  
                score1++;
                if(score1 == 5){
                    gameover.setString("Game Over!\nPlayer1 Wins!");
                    Over = true;
                    ball.setPosition(960, ball.getPosition().y);
                    moveX = moveY = 0;
                }
                else{
                    // Reset ball near left paddle for reaction time
                    ball.setPosition(p1.getPosition().x + 31, p1.getPosition().y + 40);
                }
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
            speed *= 1.02;
            // bounce back to right
            moveX = speed * cos(offset * 0.7f);
            moveY = speed * sin(offset * 0.7f);
        }
        else{
            if(ballLeft < 0){
                score2++;
                if(score2 == 5){
                    gameover.setString("Game Over!\nPlayer2 Wins!");
                    Over = true;
                    ball.setPosition(0, ball.getPosition().y);
                    moveX = moveY = 0;
                }
                else{
                    // Reset ball near right paddle for reaction time
                    ball.setPosition(p2.getPosition().x - 41, p2.getPosition().y + 40);
                }
            }
        }
    }
}

void moveBallAndPlayer(sf::Vector2f& movement1, sf::Vector2f& movement2, sf::CircleShape& ball, float& deltaTime, sf::RectangleShape& p1, sf::RectangleShape& p2, float& moveX, float& moveY){
    p1.move(movement1*deltaTime); // deltaTime is used to make the movement frame-rate independent
    p2.move(movement2*deltaTime);
    ball.move(moveX*deltaTime, moveY*deltaTime);
}

int main(){
    // creating window
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Pong");
    window.setFramerateLimit(120);
    bool Over = false; // checking for GameOver
    
    sf::Clock clock;
    sf::CircleShape ball; // creating ball
    ball.setRadius(20);
    ball.setPosition(930, 668);
    ball.setFillColor(sf::Color::Red);
    
    sf::RectangleShape p1; // player 1
    p1.setSize(sf::Vector2f(30, 120));
    p1.setPosition(2, 2);
    p1.setFillColor(sf::Color::Blue);
    
    sf::RectangleShape p2; // player 2
    p2.setSize(sf::Vector2f(30, 120));
    p2.setPosition(968, 678);
    p2.setFillColor(sf::Color::Magenta);

    sf::Vector2f movement1(0, 0.0f); // to control p1's movement
    sf::Vector2f movement2(0, 0.0f); // to control p2's movement
    // circle can travel in both x and y direction
    float moveX = 500.0;
    float moveY = 500.0;

    sf::Font font;
    font.loadFromFile("FreeRoyalty.ttf");
    sf::Text gameover;
    gameover.setFont(font);
    gameover.setCharacterSize(60);
    gameover.setPosition(300, 350);
    gameover.setFillColor(sf::Color::Red);

    // creating a score measurer for each player
    int score1 = 0; // game will end when either of them reaches a score of 5
    int score2 = 0;
    // displaying score 
    sf::Text point1, point2;
    point1.setCharacterSize(30);
    point1.setPosition(100, 10);
    point1.setFont(font);
    point1.setFillColor(sf::Color::Blue);
    point2 = point1;
    point2.setFillColor(sf::Color::Cyan);
    point2.setPosition(730, 10);

    while(window.isOpen()){
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        p1Clicks(movement1, Over);
        p2Clicks(movement2, Over);
        moveBallAndPlayer(movement1, movement2, ball, deltaTime, p1, p2, moveX, moveY);
        // controlling p1 (ensuring bound check)
        boundP1(p1);
        // controlling p2 (ensuring bound check)
        boundP2(p2);
        // controlling ball and ensuring proper GameOver
        boundBallAndGameOver(ball, p1, p2, gameover, moveX, moveY, Over, score1, score2);
        point1.setString("Player1 : "+to_string(score1));
        point2.setString("Player2 : "+to_string(score2));
        window.clear(sf::Color::Black);
        window.draw(ball);
        window.draw(p1);
        window.draw(p2);
        window.draw(gameover);
        window.draw(point1);
        window.draw(point2);
        window.display();
    }
}
