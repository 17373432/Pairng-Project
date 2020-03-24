#include "NewQtGuiClass.h"

int in = 0;

NewQtGuiClass::NewQtGuiClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowTitleHint);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(pushButton()));
	winL = new LineQtGuiClass;
	winC = new CircleQtGuiClass;
	connect(winL, SIGNAL(sendsignalL(QString)), this, SLOT(getDataL(QString)));
	connect(winC, SIGNAL(sendsignalC(QString)), this, SLOT(getDataC(QString)));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(sendData()));
}

NewQtGuiClass::~NewQtGuiClass()
{
}

void NewQtGuiClass::pushButton() {
	int index = ui.comboBox->currentIndex();
	if (index == 0) {
		in = 0;
		winC->show();
		//this->hide();
	}
	else {
		in = index;
		winL->show();
		//this->hide();
	}
	/*buf = ui.lineEdit->text();
	emit sendsignal(buf);
	this->close();*/
}

void NewQtGuiClass::getDataL(QString data) {
	if (in == 1) {
		buf = "S ";
	}
	else if (in == 2) {
		buf = "R ";
	}
	else if (in == 3) {
		buf = "L ";
	}
	buf.append(data);
	if (data[0] == 'N') {
		buf = data;
	}
}

void NewQtGuiClass::getDataC(QString data) {
	buf = "C ";
	buf.append(data);
	if (data[0] == 'N') {
		buf = data;
	}
}

void NewQtGuiClass::sendData() {
	emit sendsignal(buf);
	buf = "";
	this->close();
}
