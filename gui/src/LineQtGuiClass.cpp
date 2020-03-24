#include "LineQtGuiClass.h"

LineQtGuiClass::LineQtGuiClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	QRegExp rx("^-?\\d{1,6}$"); 
	QRegExpValidator* v = new QRegExpValidator(rx, this);

	ui.lineEdit->setValidator(v);
	ui.lineEdit_2->setValidator(v);
	ui.lineEdit_3->setValidator(v);
	ui.lineEdit_4->setValidator(v);

	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowTitleHint);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(getDataL()));
}

LineQtGuiClass::~LineQtGuiClass()
{
}

void LineQtGuiClass::getDataL() {
	buf = ui.lineEdit->text();
	buf2 = ui.lineEdit_2->text();
	buf3 = ui.lineEdit_3->text();
	buf4 = ui.lineEdit_4->text();
	if (buf.size() == 0 || buf2.size() == 0 || buf3.size() == 0 || buf4.size() == 0) {
		ui.lineEdit->clear();
		ui.lineEdit_2->clear();
		ui.lineEdit_3->clear();
		ui.lineEdit_4->clear();
		buf = "None";
		emit sendsignalL(buf);
		this->close();
		return;
	}
	buf.append(" ");
	buf.append(buf2);
	buf.append(" ");
	buf.append(buf3);
	buf.append(" ");
	buf.append(buf4);
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.lineEdit_4->clear();
	emit sendsignalL(buf);
	this->close();
}
