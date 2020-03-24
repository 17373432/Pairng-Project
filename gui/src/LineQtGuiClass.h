#pragma once

#include <QWidget>
#include "ui_LineQtGuiClass.h"
#include <QChart>
#include <QChartView>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>
#include <QPaintEvent>
#include <QFileDialog>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>
#include <QListWidgetItem>
#include <QDebug>

class LineQtGuiClass : public QWidget
{
	Q_OBJECT
public slots:
	void getDataL();

signals:
	void sendsignalL(QString);

public:
	LineQtGuiClass(QWidget *parent = Q_NULLPTR);
	~LineQtGuiClass();
	QString buf, buf2, buf3, buf4;

private:
	Ui::LineQtGuiClass ui;
};
