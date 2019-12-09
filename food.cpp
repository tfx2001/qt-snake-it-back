#include "food.h"

Food::Food(QGraphicsItem *parent) : QGraphicsItem(parent)
{
	setPos(0, 0);
}

QPoint Food::gridPos() const {return m_gridPos;}

void Food::setGridPos(QPoint p){
	m_gridPos = p;
	setPos(p.rx() * gridSize, p.ry() * gridSize);
}

QRectF Food::boundingRect() const
{
	return QRectF(0, 0, gridSize, gridSize);
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHints(QPainter::Antialiasing);
	// 四个矩形
	painter->fillRect(QRectF(-foodSize, -foodSize * 3, foodSize * 2, foodSize * 2), QColor::fromRgb(colorFood));
	painter->fillRect(QRectF(-foodSize, foodSize, foodSize * 2, foodSize * 2), QColor::fromRgb(colorFood));
	painter->fillRect(QRectF(-foodSize * 3, -foodSize, foodSize * 2, foodSize * 2), QColor::fromRgb(colorFood));
	painter->fillRect(QRectF(foodSize,  -foodSize, foodSize * 2, foodSize * 2), QColor::fromRgb(colorFood));
	// 画线
	painter->fillRect(QRectF(-foodSize * 3, -lineWidth / 2.0, foodSize * 6, lineWidth), QColor::fromRgb(colorGrass));
	painter->fillRect(QRectF(-lineWidth / 2.0, -foodSize * 3, lineWidth, foodSize * 6), QColor::fromRgb(colorGrass));
	// 画Shape
//	painter->drawPath(shape());
}

QPainterPath Food::shape() const
{
	QPainterPath sp;
	sp.addRect(-gridSize / 4, -gridSize / 4, gridSize / 2, gridSize / 2);
	return sp;
}
