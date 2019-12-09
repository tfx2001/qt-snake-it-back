#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QPainter>
#include <GameConfig.h>
#include <QDebug>

enum SnakeDirection
{
	Up = 1,
	Right = 2,
	Down = 3,
	Left = 4
};

class Snake : public QGraphicsItem
{
public:
	Snake(QPoint pos, int length, SnakeDirection direction, QGraphicsItem* parent = nullptr);
	Snake(Snake& s);

	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QPainterPath shape() const override;

	SnakeDirection direction() const;
	void setDirection(const SnakeDirection d);
	QVector<QPoint> body();
	bool outOfBorder();
	bool collidSelf();
	void dead(bool d);
	bool isDead();
	void move();
	void grow();
	QPainterPath head();
	void setCurrentFrame(int currentFrame);
	int interval() const;
	void setInterval(int interval);

private:
	QVector<QPoint> m_body;
	SnakeDirection m_directiron;
	QVector<QVector<QPoint>> m_frame;
	bool m_dead = false;
	int m_currentFrame = 0;
	bool enableSetDirection;
	int m_interval = 50;
	int m_tick = 50;
};

#endif // SNAKE_H
