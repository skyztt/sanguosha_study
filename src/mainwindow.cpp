#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscene.h"

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QVariant>
#include <QMessageBox>
#include <QGLWidget>
#include <QTime>
#include "roomscene.h"
#include "server.h"
#include "engine.h"
#include "connectiondialog.h"
#include "QTcpSocket"
#include "client.h"
#include "QTextEdit"

class FitView : public QGraphicsView
{
public:
    FitView(QGraphicsScene *scene) : QGraphicsView(scene) {
        setSceneRect(Config.Rect);
		if (Config.UseOpenGL)
			setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    }

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QGraphicsView::resizeEvent(event);
        if(Config.FitInView)
            fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    Config.init();
	connection_dialog = new ConnectionDialog(this);
	//connect(ui->actionStart_Game, SIGNAL(triggered()), connection_dialog, SLOT(show()));
	connect(ui->actionStart_Game, SIGNAL(triggered()), connection_dialog, SLOT(on_connectButton_clicked()));
	
	connect(connection_dialog, SIGNAL(accepted()), this, SLOT(startConnection()));
	connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    

    StartScene *start_scene = new StartScene;
	QList<QAction*> actions;
	actions << ui->actionStart_Game << ui->actionConfigure << ui->actionStart_Server
		<< ui->actionGeneral_Preview << ui->actionAcknowledgement << ui->actionExit;
	for (auto pAction : actions) {
		start_scene->addButton(pAction);
	}

    scene = start_scene;
    FitView *view = new FitView(scene);

    setCentralWidget(view);

//    if(Config.TitleMusic)
//        Config.TitleMusic->play();

    restoreFromConfig();
}

void MainWindow::restoreFromConfig(){
    resize(Config.value("WindowSize").toSize());
    move(Config.value("WindowPosition").toPoint());
}

void MainWindow::closeEvent(QCloseEvent *){
    Config.setValue("WindowSize", size());
    Config.setValue("WindowPosition", pos());
}

MainWindow::~MainWindow()
{    
    delete ui;
}

void MainWindow::gotoScene(QGraphicsScene *scene){
    if(scene == NULL){
        ui->actionExit->trigger();
        return;
    }

    QGraphicsView *view = qobject_cast<QGraphicsView *>(centralWidget());
    view->setScene(scene);
    //delete this->scene;
    this->scene->deleteLater();
    this->scene = scene;
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton result;
    result = QMessageBox::question(this,
                                   tr("Sanguosha"),
                                   tr("Are you sure to exit?"),
                                   QMessageBox::Ok | QMessageBox::Cancel);
    if(result == QMessageBox::Ok)
        close();
}

void MainWindow::startGame()
{
	ui->actionStart_Game->setEnabled(false);
	ui->actionStart_Server->setEnabled(false);

	gotoScene(new RoomScene);
}

void MainWindow::connectionError(const QString &error_msg)
{
	QMessageBox::warning(this, tr("Connection failed"), error_msg);
}

void MainWindow::on_actionStart_Server_triggered()
{
	if (!server_) {
		server_ = new Server(this);

		if (!log4Server_) {
			log4Server_ = new QTextEdit;
			log4Server_->setReadOnly(true);
			connect(server_, &Server::server_message, log4Server_, &QTextEdit::append);
		}		

		if (!server_->start()) {
			QMessageBox::warning(this, "Warning", tr("Can not start server!"));
			return;
		}
	}	

	ui->actionStart_Game->setEnabled(false);
	ui->actionStart_Server->setEnabled(false);	
	log4Server_->show();
	
#if 0
	StartScene *start_scene = qobject_cast<StartScene *>(scene);
	if (start_scene) {
		start_scene->switchToServer(server);
	}
#endif
}

void MainWindow::startConnection()
{
	Client *client = new Client(this);

	connect(client, SIGNAL(errorMessage(QString)), SLOT(connectionError(QString)));
	connect(client, SIGNAL(connected()), SLOT(startGame()));
}
