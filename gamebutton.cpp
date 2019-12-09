#include "gamebutton.h"

GameButton::GameButton(QGraphicsItem* parent) : QGraphicsObject(parent)
{
	setCursor(Qt::PointingHandCursor);
	setFlag(QGraphicsItem::ItemClipsToShape);
	setFlag(QGraphicsItem::ItemIsSelectable);
}

QRectF GameButton::boundingRect() const
{
	return QRectF(-64, -24, 128, 48);
}

void GameButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QFont font("Consolas", 22);
	QPainterPath path;
	path.addRoundedRect(boundingRect(), 24, 24);
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->fillPath(path, QBrush(QColor::fromRgb(colorSnake)));
	painter->setFont(font);
	painter->setPen(QColor::fromRgb(colorGrass));
	painter->drawText(-40, 9, "Start");
}

QPainterPath GameButton::shape() const
{
	QPainterPath path;
	path.addRoundedRect(boundingRect(), 24, 24);
	return path;
}

void GameButton::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	emit clicked();
	event->accept();
}
