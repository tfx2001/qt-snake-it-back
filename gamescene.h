#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QRandomGenerator>
#include <QDateTime>
#include <QKeyEvent>
#include <QTextDocument>
#include <QTextOption>
#include <QDebug>
#include <food.h>
#include <snake.h>
#include <deadsnake.h>
#include <gamebutton.h>

class GameScene : public QGraphicsScene
{
	Q_OBJECT
public:
	// TODO: 添加动画
	GameScene(QObject* parent = nullptr);

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
	Food* m_food;
	Snake* m_snake;
	DeadSnake* m_deadSnake;
	QTimer* m_gameTimer;
	QRandomGenerator* m_random;
	GameButton* m_button;
	QGraphicsRectItem* m_background;
	QGraphicsTextItem* m_text;
	bool m_running = false;
	int m_life = 0;

	void newRound(bool init);

private slots:
	void tick();
	void newGame();
	void endGame();
};

#endif // GAMESCENE_H
