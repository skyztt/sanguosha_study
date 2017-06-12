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

	Engine *engine = nullptr;

private slots:
    void gotoScene(QGraphicsScene *scene);

    void on_actionExit_triggered();
	void on_actionStart_Game_triggered();
	void on_actionStart_Server_triggered();
	void scriptException(const QScriptValue &exception);
};

#endif // MAINWINDOW_H
