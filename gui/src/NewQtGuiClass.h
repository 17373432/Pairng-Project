#pragma once

#include <QWidget>
#include "ui_NewQtGuiClass.h"
#include "LineQtGuiClass.h"
#include "CircleQtGuiClass.h"

class NewQtGuiClass : public QWidget
{
	Q_OBJECT

public slots:
	void pushButton();
	void getDataL(QString data);
	void getDataC(QString data);
	void sendData();

signals:
	void sendsignal(QString);
	void sendsignalC(QString);
	void sendsignalL(QString);

public:
	NewQtGuiClass(QWidget *parent = Q_NULLPTR);
	~NewQtGuiClass();
	QString buf;

private:
	Ui::NewQtGuiClass ui;
	LineQtGuiClass *winL;
	CircleQtGuiClass *winC;
};
