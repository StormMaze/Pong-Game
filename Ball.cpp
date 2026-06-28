#include "Ball.h"

Ball::Ball(float startX, float startY, float radius) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setRadius(radius);
    m_Shape.setPosition(m_Position);
    m_InitialPosition = m_Position;
}
Vector2f     Ball::getPosition() { return m_Position; }
FloatRect    Ball::getBounds() {return m_Shape.getGlobalBounds();}
CircleShape &Ball::getShape() { return m_Shape; }
void         Ball::bounceSides(Vector2i resolution) { 
    if(m_DirectionX<0){
        m_Position.x = 1;
    }else{
        m_Position.x = resolution.x - m_Shape.getLocalBounds().width-1;
    }
    m_Shape.setPosition(m_Position);
    m_DirectionX = -m_DirectionX; 
}
void         Ball::bounceByBat(int batPosY) { 
    m_Position.y = batPosY - m_Shape.getLocalBounds().height -1;
    m_Shape.setPosition(m_Position);    
    m_DirectionY = -m_DirectionY; 
}
void         Ball::bounceTop() { 
    m_Position.y = 1;
    m_Shape.setPosition(m_Position);
    m_DirectionY = -m_DirectionY; 
}
void         Ball::bounceBottom() { m_Position = m_InitialPosition; }
void         Ball::update(Time dt) {
    m_Position.x+= m_DirectionX * m_Speed*dt.asSeconds();
    m_Position.y+= m_DirectionY * m_Speed*dt.asSeconds();
    m_Shape.setPosition(m_Position);
}
void Ball::reset(){
    m_Position = m_InitialPosition;
    m_Shape.setPosition(m_Position);
}