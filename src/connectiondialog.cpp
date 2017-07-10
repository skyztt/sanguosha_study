#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include "settings.h"

#include <QTcpSocket>
#include "engine.h"
#include "general.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    ui->nameLineEdit->setText(Config.UserName);
    ui->hostLineEdit->setText(Config.HostAddress);
    ui->portLineEdit->setValidator(new QIntValidator(0, 65535, ui->portLineEdit));
    ui->portLineEdit->setText(QString::number(Config.Port));

    // fix this dialog
    setFixedSize(size());

	for (General * general : Engine::getInstance()->getAllGenerals()) {
		QString iconPath = general->getPixmapPath("big");
		QString engName = general->objectName();
		QString name = Engine::getInstance()->translate(engName);
		if (name.isEmpty()) {
			name = engName;
		}
		QListWidgetItem *item = new QListWidgetItem(QIcon(iconPath), name, ui->generalList);
		item->setData(Qt::UserRole, engName);
	}
	connect(ui->generalList, &QListWidget::itemDoubleClicked, this, &ConnectionDialog::chooseUserGeneral);
	connect(ui->changeAvatarBtn, &QPushButton::clicked, this, [this]() {
		auto selectionItems = ui->generalList->selectedItems();
		if (!selectionItems.isEmpty()) {
			chooseUserGeneral(selectionItems.at(0));
		}
	});

	QString strUserGeneral(Config.userGeneral);
	if (General *userGeneral = Engine::getInstance()->getGeneral(strUserGeneral)) {
		ui->avatar_pic->setPixmap(QPixmap(userGeneral->getPixmapPath("big")));
		for (int i = 0, j = ui->generalList->count(); i < j; ++i) {
			if (QListWidgetItem *item = ui->generalList->item(i)) {
				QString generalName = item->data(Qt::UserRole).toString();
				if (generalName == Config.userGeneral) {
					ui->generalList->setCurrentItem(item, QItemSelectionModel::Select);
					break;
				}
			}
		}		
	}
    // do connection
//    QTcpSocket *socket = new QTcpSocket(this);
//    socket->connectToHost("127.0.0.1", Config.Port);
//    connect(socket, SIGNAL(connected()), this, SLOT(enterRoom()));
//    socket->waitForConnected();
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_connectButton_clicked()
{
	Config.UserName = ui->nameLineEdit->text();
	Config.HostAddress = ui->hostLineEdit->text();
	Config.Port = ui->portLineEdit->text().toUShort();
	accept();
}

void ConnectionDialog::chooseUserGeneral(QListWidgetItem *item)
{
	if (item) {
		QString generalName = item->data(Qt::UserRole).toString();
		if (General *g = Engine::getInstance()->getGeneral(generalName)) {
			ui->avatar_pic->setPixmap(QPixmap(g->getPixmapPath("big")));
			Config.userGeneral = generalName;
		}
	}
}
