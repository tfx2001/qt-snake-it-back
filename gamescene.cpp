#include "gamescene.h"

GameScene::GameScene(QObject* parent) : QGraphicsScene(parent)
{
	// PV Initalize
	// Random Generator
	m_random = new QRandomGenerator(QDateTime::currentDateTime().toTime_t());
	// Dead Snake
	m_deadSnake = new DeadSnake();
	addItem(m_deadSnake);
	// Game Button
	m_button = new GameButton();
	addItem(m_button);
	m_button->setPos(300, 200);
	connect(m_button, SIGNAL(clicked()), this, SLOT(newGame()));
	// Background Rectangle
	m_background = addRect(-10, -40, 620, 30, QPen(Qt::NoPen), QBrush(QColor::fromRgb(colorFood)));
	// Score
	m_text = addText("HP: 0");
	QFont font;
	QTextOption option = m_text->document()->defaultTextOption();
	// Font
	font.setFamily("Microsoft YaHei");
	font.setPointSize(14);
	// Text
	m_text->setFont(font);
	m_text->setPos({0, -42});
	// Align
	m_text->setTextWidth(600);
	option.setAlignment(Qt::AlignCenter);
	m_text->document()->setDefaultTextOption(option);
	m_text->setDefaultTextColor(QColor::fromRgb(colorGrass));
	m_text->setVisible(false);
	//Timer Initalize
	m_gameTimer = new QTimer(this);
	connect(m_gameTimer, SIGNAL(timeout()), this, SLOT(tick()));
}

void GameScene::tick()
{
	if (autoPlay)
	{
		if (m_food->gridPos().rx() < m_snake->body()[0].rx() && m_snake->direction() != SnakeDirection::Right)
		{
			m_snake->setDirection(SnakeDirection::Left);
		}
		else if (m_food->gridPos().rx() < m_snake->body()[0].rx() && m_snake->direction() == SnakeDirection::Right)
		{
			m_snake->setDirection(SnakeDirection::Up);
		}
		else if (m_food->gridPos().rx() > m_snake->body()[0].rx() && m_snake->direction() != SnakeDirection::Left)
		{
			m_snake->setDirection(SnakeDirection::Right);
		}
		else if (m_food->gridPos().rx() > m_snake->body()[0].rx() && m_snake->direction() == SnakeDirection::Left)
		{
			m_snake->setDirection(SnakeDirection::Down);
		}
		else if (m_food->gridPos().ry() < m_snake->body()[0].ry() && m_snake->direction() != SnakeDirection::Down)
		{
			m_snake->setDirection(SnakeDirection::Up);
		}
		else if (m_food->gridPos().ry() < m_snake->body()[0].ry() && m_snake->direction() == SnakeDirection::Down)
		{
			m_snake->setDirection(SnakeDirection::Left);
		}
		else if (m_food->gridPos().ry() > m_snake->body()[0].ry() && m_snake->direction() != SnakeDirection::Up)
		{
			m_snake->setDirection(SnakeDirection::Down);
		}
		else if (m_food->gridPos().ry() > m_snake->body()[0].ry() && m_snake->direction() == SnakeDirection::Up)
		{
			m_snake->setDirection(SnakeDirection::Right);
		}
	}
	if (m_snake->collidesWithItem(m_food))
	{
		m_food->setGridPos({m_random->bounded(0, 31), m_random->bounded(0, 21)});
		m_food->update();
		m_snake->grow();
		m_snake->setInterval(m_snake->interval() - 5 > 0 ? m_snake->interval() - 5 : 5);
	}
	else
	{
		m_snake->move();
	}
	m_deadSnake->move();
	m_snake->update();
	m_deadSnake->update();
	if (m_snake->outOfBorder() || m_snake->collidSelf() || m_deadSnake->collidesWithPath(m_snake->head()))
	{
		if (--m_life)
			newRound(false);
		else
			endGame();
	}
}

void GameScene::newGame()
{
	m_button->setVisible(false);
	m_text->setVisible(true);
	m_running = true;
	m_life = 5;
	newRound(true);
}

void GameScene::endGame()
{
	m_gameTimer->stop();
	m_button->setVisible(true);
	m_text->setVisible(false);
	m_running = false;
	m_deadSnake->removeAllSnake();
	this->removeItem(m_snake);
	this->removeItem(m_food);
	delete m_snake;
	delete m_food;
}

void GameScene::keyPressEvent(QKeyEvent* event)
{
	if (!m_running)
		return;
	else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
		m_snake->setDirection(SnakeDirection::Up);
	else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
		m_snake->setDirection(SnakeDirection::Down);
	else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
		m_snake->setDirection(SnakeDirection::Left);
	else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
		m_snake->setDirection(SnakeDirection::Right);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mouseReleaseEvent(event);
}

void GameScene::newRound(bool init)
{
	m_gameTimer->stop();
	if (!init)
	{
		m_deadSnake->addSnake(*m_snake);
		m_deadSnake->restart();
		this->removeItem(m_food);
		this->removeItem(m_snake);
		delete m_snake;
		delete m_food;
	}
	m_text->setPlainText(QString("HP: %1").arg(m_life));
	m_snake = new Snake({m_random->bounded(5, 25), m_random->bounded(5, 15)}, 3, SnakeDirection(m_random->bounded(1, 5)));
	m_food = new Food();
	this->addItem(m_food);
	this->addItem(m_snake);
	m_food->setGridPos({m_random->bounded(0, 30), m_random->bounded(0, 20)});
	m_gameTimer->start(10);
}
