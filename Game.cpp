#include "Ball.cpp"
#include "Bat.cpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;
int main() {
#pragma region VM
    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    VideoMode    vm(resolution.x, resolution.y);
    RenderWindow window(vm, "Pong Game", Style::Fullscreen);
#pragma endregion
#pragma region Variables
    bool gamePaused = true;
    bool gameOver   = true;
    int  batWidth   = 100;
    int  batheight  = 10;
    int  ballRadius = 10;
    int  score      = 0;
    int  lives      = 3;
    int  batPosY    = 0;
#pragma endregion

#pragma region Loading_Assets
    Font font;
    font.loadFromFile("fonts/Chicago.ttf");

    Text messageText;
    messageText.setCharacterSize(50);
    messageText.setFont(font);
    messageText.setFillColor(Color::Cyan);
    messageText.setString("Press Enter to start");
    messageText.setOrigin(messageText.getLocalBounds().width / 2, messageText.getLocalBounds().height / 2);
    messageText.setPosition(resolution.x / 2, resolution.y / 2);

    Text scoreLivesText;
    scoreLivesText.setCharacterSize(25);
    scoreLivesText.setFont(font);
    scoreLivesText.setFillColor(Color::Cyan);
    scoreLivesText.setString("Score: 0  Lives: 3");
    scoreLivesText.setPosition(10, 10);
#pragma endregion

    Ball ball(resolution.x / 2, 20, ballRadius);
    batPosY = resolution.y - batheight - 20;
    Bat  bat((resolution.x - batWidth) / 2, batPosY, batWidth, batheight);

    Clock clock;
    Time  dt;
    // ball.getShape().setFillColor(Color::Red);
    while (window.isOpen()) {
        Event event;
        dt = clock.restart();
        while (window.pollEvent(event)) { // handling single event
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == Keyboard::Enter && gameOver) {
                    gameOver   = false;
                    gamePaused = false;
                    score      = 0;
                    lives      = 3;
                }
            }
        }
        // handling continuous events
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            bat.moveLeft();
        } else {
            bat.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            bat.moveRight();
        } else {
            bat.stopRight();
        }

        if (!gamePaused) {
            if (ball.getPosition().x <= 0) { // Left panel
                ball.bounceSides(resolution);
            }
            if (ball.getPosition().x + ball.getBounds().width >= resolution.x) { // Right panel
                ball.bounceSides(resolution);
            }
            if (ball.getPosition().y <= 0) { // Top panel
                ball.bounceTop();
            }
            if (ball.getPosition().y >= resolution.y) { // Bottom panel
                ball.reset();
                lives--;
                if (lives == 0) {
                    gameOver   = true;
                    gamePaused = true;
                }
            }
            if (bat.getBounds().intersects(ball.getBounds())) {
                ball.bounceByBat(batPosY);
                score++;
            }
            std::stringstream ss;
            ss << "Score: " << score << "  Lives: " << lives;
            scoreLivesText.setString(ss.str());

            ball.update(dt);
            bat.update(dt, resolution);
        }
        window.clear();
        window.draw(scoreLivesText);
        window.draw(ball.getShape());
        window.draw(bat.getShape());
        if (gameOver)
            window.draw(messageText);
        window.display();
    }
}