#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
    class ConnectionDialog;
}

class QListWidgetItem;

class ConnectionDialog : public QDialog {
    Q_OBJECT
public:
    ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();
public slots:
	void on_connectButton_clicked();
	void chooseUserGeneral(QListWidgetItem *item);

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
