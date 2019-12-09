#ifndef DEADSNAKE_H
#define DEADSNAKE_H

#include <QGraphicsItemGroup>
#include <snake.h>

class DeadSnake : public QGraphicsItemGroup
{
public:
	DeadSnake(QGraphicsItem* parent = nullptr);
	QRectF boundingRect() const override;
	void addSnake(Snake snake);
	void removeAllSnake();
	QPainterPath shape() const override;
	void move();
	void restart();

private:
	QVector<Snake*> m_snakes;
};

#endif // DEADSNAKE_H
