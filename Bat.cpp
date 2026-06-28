#include <SFML/Graphics.hpp>
using namespace sf;

class Bat {
  private:
    RectangleShape m_Shape;
    Vector2f       m_Position;
    Vector2f       m_Initial_Position;
    float          m_Speed = 500.0f;

    bool m_MovingLeft  = false;
    bool m_MovingRight = false;

  public:
    Bat(float startX, float startY, int width, int height);
    RectangleShape& getShape();
    FloatRect  getBounds();
    void           moveLeft();
    void           stopLeft();
    void           moveRight();
    void           stopRight();
    void           update(Time dt,Vector2i resolution);
};

Bat::Bat(float startX, float startY, int width, int height) {
    m_Position.x       = startX;
    m_Position.y       = startY;
    m_Initial_Position = m_Position;
    m_Shape.setPosition(m_Position);
    m_Shape.setSize(Vector2f(width, height));
}
RectangleShape & Bat::getShape() { return m_Shape; }
FloatRect    Bat::getBounds() {return m_Shape.getGlobalBounds();}
void Bat::moveLeft() { m_MovingLeft = true; }
void Bat::stopLeft() { m_MovingLeft = false; }
void Bat::moveRight() { m_MovingRight = true; }
void Bat::stopRight() { m_MovingRight = false; }
void Bat::update(Time dt,Vector2i resolution) {
    if(m_MovingLeft && m_Position.x>0){
        m_Position.x-= m_Speed*dt.asSeconds();
    }
    if(m_MovingRight && (m_Position.x+m_Shape.getLocalBounds().width)<resolution.x){
        m_Position.x+= m_Speed*dt.asSeconds();
    }
    m_Shape.setPosition(m_Position);
}