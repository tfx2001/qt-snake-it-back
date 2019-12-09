#include "app.h"
#include "ui_app.h"

App::App(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::App)
{
	ui->setupUi(this);

	// GraphicView Initalize
	scene = new GameScene(this);
	this->setFixedSize(size());
	this->scene->setSceneRect(-5, -20, 610, 410);
	ui->graphicsView->setStyleSheet("padding: 0; border: 0;");
	ui->graphicsView->setScene(this->scene);
	ui->graphicsView->setBackgroundBrush(QColor::fromRgb(colorGrass));
}

App::~App()
{
	delete ui;
}

