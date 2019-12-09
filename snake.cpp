#include "snake.h"

Snake::Snake (QPoint pos, int length, SnakeDirection direction, QGraphicsItem* parent) : QGraphicsItem(parent)
{
	setFlag(QGraphicsItem::ItemIsFocusable, false);
	for (int i = 0; i < length; i++)
	{
		switch (direction)
		{
			case (SnakeDirection::Up):
				m_body.append({pos.rx(), pos.ry() + i});
				break;
			case (SnakeDirection::Right):
				m_body.append({pos.rx() - i, pos.ry()});
				break;
			case (SnakeDirection::Down):
				m_body.append({pos.rx(), pos.ry() - i});
				break;
			case (SnakeDirection::Left):
				m_body.append({pos.rx() + i, pos.ry()});
				break;
		}
	}
	m_directiron = SnakeDirection(direction);
	setPos (0, 0);
}

// 复制构造函数
Snake::Snake (Snake& s)
{
	m_frame = s.m_frame;
	m_dead = s.isDead();
}

QRectF Snake::boundingRect() const
{
	return QRectF (-10, -10, 620, 420);
}

void Snake::paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHints (QPainter::Antialiasing);
	QColor snakeColor = m_dead ? QColor::fromRgb (colorDead) : QColor::fromRgb (colorSnake);
	foreach (auto p, m_body)
	{
		int t_pos[2] = {p.x()* gridSize - gridSize / 2, p.y()* gridSize - gridSize / 2};
		painter->fillRect (t_pos[0], t_pos[1], gridSize, gridSize, snakeColor);
		painter->fillRect (t_pos[0] + 2, t_pos[1] + 2, gridSize - 4, gridSize - 4, QColor::fromRgb (colorGrass));
		painter->fillRect (t_pos[0] + 4, t_pos[1] + 4, gridSize - 8, gridSize - 8, snakeColor);
	}
	//      painter->drawPath(shape());
//	painter->drawRect(0, 0, 600, 400);
}

QPainterPath Snake::shape() const
{
	QPainterPath sp;
	foreach (auto p, m_body)
	{
		int t_pos[2] = {p.x()* gridSize - gridSize / 2, p.y()* gridSize - gridSize / 2};
		sp.addRect (QRectF (t_pos[0], t_pos[1], gridSize, gridSize));
	}
	return sp;
}

SnakeDirection Snake::direction() const
{
	return m_directiron;
}

void Snake::setDirection (const SnakeDirection d)
{
	if (abs (m_directiron - d) != 2 && enableSetDirection)
	{
		m_directiron = d;
		enableSetDirection = false;
	}
}

QVector<QPoint> Snake::body()
{
	return m_body;
}

bool Snake::outOfBorder()
{
	QPoint p = m_body[0];
	return (p.rx() < 0 || p.rx() > 30 || p.ry() < 0 || p.ry() > 20);
}

bool Snake::collidSelf()
{
	QPoint p = m_body[0];
	for (auto i = m_body.begin() + 2; i != m_body.end(); i++)
	{
		if (p == *i)
			return true;
	}
	return false;
}

void Snake::dead (bool d)
{
	m_dead = d;
}

bool Snake::isDead()
{
	return m_dead;
}



void Snake::move()
{
	if (m_dead)
	{
		if (m_currentFrame < m_frame.length())
			m_body = m_frame[m_currentFrame++];
		else
			this->setVisible (false);
	}
	else
	{
		m_frame.append(m_body);
		if (m_tick-- == 0)
		{
			m_tick = m_interval;
			switch (m_directiron)
			{
				case Up:
					m_body.prepend({m_body[0].x(), m_body[0].y() - 1});
					break;
				case Right:
					m_body.prepend({m_body[0].x() + 1, m_body[0].y()});
					break;
				case Down:
					m_body.prepend({m_body[0].x(), m_body[0].y() + 1});
					break;
				case Left:
					m_body.prepend({m_body[0].x() - 1, m_body[0].y()});
			}
			m_body.pop_back();
			enableSetDirection = true;
		}
	}
}

void Snake::grow()
{
	m_body = m_frame.last();
	switch (m_directiron)
	{
		case Up:
			m_body.prepend ({m_body[0].x(), m_body[0].y() - 1});
			break;
		case Right:
			m_body.prepend ({m_body[0].x() + 1, m_body[0].y()});
			break;
		case Down:
			m_body.prepend ({m_body[0].x(), m_body[0].y() + 1});
			break;
		case Left:
			m_body.prepend ({m_body[0].x() - 1, m_body[0].y()});
	}
}

QPainterPath Snake::head()
{
	QPainterPath path;
	path.addRect (QRectF (m_body[0].rx() * gridSize - gridSize / 4, m_body[0].ry() * gridSize - gridSize / 4, gridSize / 2, gridSize / 2));
	return path;
}

void Snake::setCurrentFrame (int currentFrame)
{
	m_currentFrame = currentFrame;
}

int Snake::interval() const
{
	return m_interval;
}

void Snake::setInterval(int interval)
{
	m_interval = interval;
}
