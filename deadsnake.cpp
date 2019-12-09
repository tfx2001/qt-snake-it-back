#include "deadsnake.h"

DeadSnake::DeadSnake(QGraphicsItem* parent) : QGraphicsItemGroup(parent)
{
	setPos(0, 0);
}

QRectF DeadSnake::boundingRect() const
{
	return QRectF(-10, -10, 620, 420);
}

void DeadSnake::addSnake(Snake s)
{
	Snake* ds = new Snake(s);
	ds->dead(true);
	this->addToGroup(ds);
	m_snakes.append(ds);
}

void DeadSnake::removeAllSnake()
{
	foreach (auto snake, m_snakes)
	{
		removeFromGroup(snake);
		delete snake;
	}
	m_snakes.clear();
}

QPainterPath DeadSnake::shape() const
{
	QPainterPath path;
	foreach (auto s, this->childItems())
	{
		if (s->isVisible())
			path += s->shape();
	}
	return path;
}

void DeadSnake::move()
{
	for (auto i = m_snakes.begin(); i != m_snakes.end(); i++)
	{
		(*i)->move();
	}
}

void DeadSnake::restart()
{
	for (auto i = m_snakes.begin(); i != m_snakes.end(); i++)
	{
		(*i)->setVisible(true);
		(*i)->setCurrentFrame(0);
	}
}
