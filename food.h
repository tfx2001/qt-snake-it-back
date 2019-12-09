#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsItem>
#include <QPainter>
#include <GameConfig.h>

#define foodSize 3
#define lineWidth 2

class Food : public QGraphicsItem
{
public:
	Food(QGraphicsItem *parent = nullptr);

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	QPainterPath shape() const override;

	QPoint gridPos() const;
	void setGridPos(QPoint p);

private:
	QPoint m_gridPos;
};

#endif // FOOD_H
