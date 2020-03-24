#include "CircleQtGuiClass.h"

CircleQtGuiClass::CircleQtGuiClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QRegExp rx("^-?\\d{1,6}$");
	QRegExpValidator* v = new QRegExpValidator(rx, this);

	QIntValidator *intValidator = new QIntValidator;
	intValidator->setRange(-100000, 100000);
	ui.lineEdit->setValidator(v);
	ui.lineEdit_2->setValidator(v);
	intValidator->setRange(0, 100000);
	ui.lineEdit_3->setValidator(intValidator);

	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowTitleHint);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(getDataC()));
}

CircleQtGuiClass::~CircleQtGuiClass()
{
}

void CircleQtGuiClass::getDataC() {
	buf = ui.lineEdit->text();
	buf2 = ui.lineEdit_2->text();
	buf3 = ui.lineEdit_3->text();
	//qDebug() << buf.size();
	if (buf.size() == 0 || buf2.size() == 0 || buf3.size() == 0) {
		ui.lineEdit->clear();
		ui.lineEdit_2->clear();
		ui.lineEdit_3->clear();
		buf = "None";
		emit sendsignalC(buf);
		this->close();
		return;
	}
	buf.append(" ");
	buf.append(buf2);
	buf.append(" ");
	buf.append(buf3);
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	emit sendsignalC(buf);
	this->close();
}
