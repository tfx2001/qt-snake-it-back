#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QCursor>
#include <QDebug>
#include <GameConfig.h>

class GameButton : public QGraphicsObject
{
	Q_OBJECT
public:
	GameButton(QGraphicsItem* parent = nullptr);
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QPainterPath shape() const override;

protected:
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

signals:
	void clicked();
};

#endif // GAMEBUTTON_H
