#pragma once

#include <QWidget>
#include "ui_CircleQtGuiClass.h"
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


class CircleQtGuiClass : public QWidget
{
	Q_OBJECT

public slots:
	void getDataC();

signals:
	void sendsignalC(QString);

public:
	CircleQtGuiClass(QWidget *parent = Q_NULLPTR);
	~CircleQtGuiClass();
	QString buf, buf2, buf3;

private:
	Ui::CircleQtGuiClass ui;
};
