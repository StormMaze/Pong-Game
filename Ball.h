#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;

class Ball{
    private:
        Vector2f m_Position;
        Vector2f m_InitialPosition;
        CircleShape m_Shape;
        float m_Speed = 1000;
        float m_DirectionX = 0.5f;
        float m_DirectionY = 0.5f;

    public:
        Ball(float startX,float startY, float radius);
        Vector2f getPosition();
        FloatRect getBounds();
        CircleShape& getShape();
        void bounceSides(Vector2i resolution);
        void bounceByBat(int batPosY);
        void bounceTop();
        void bounceBottom();
        void update(Time dt);
        void reset();
};