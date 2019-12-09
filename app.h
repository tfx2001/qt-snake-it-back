#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QGraphicsView>
#include <gamescene.h>
#include <GameConfig.h>


QT_BEGIN_NAMESPACE
namespace Ui { class App; }
QT_END_NAMESPACE

class App : public QWidget
{
	Q_OBJECT

public:
	App(QWidget *parent = nullptr);
	~App();

private:
	Ui::App *ui;
	GameScene *scene;
};
#endif // APP_H
