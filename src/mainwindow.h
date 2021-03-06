#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QSettings>

namespace Ui {
    class MainWindow;
}

class QScriptValue;
class Engine;
class ConnectionDialog;
class Server;
class QTextEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = nullptr;

    void restoreFromConfig();

	ConnectionDialog *connection_dialog = nullptr;
	Server *server_ = nullptr;
	QTextEdit *log4Server_ = nullptr;

private slots:
    void gotoScene(QGraphicsScene *scene);

    void on_actionExit_triggered();	
	void on_actionStart_Server_triggered();

	void startConnection();

	void startGame();

	void connectionError(const QString &error_msg);
};

#endif // MAINWINDOW_H
