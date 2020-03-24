#include "QtPairProject.h"

int allNum = 0;

QtPairProject::QtPairProject(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QIntValidator *intValidator = new QIntValidator;
	intValidator->setRange(0, 100000);
	ui.lineEdit->setValidator(intValidator);

	//ui.scrollArea->setGeometry(0, 0, 720, 1000);
	ui.scrollArea->setWidget(ui.scrollAreaWidgetContents);

	ui.widget->installEventFilter(this);
	//QChartView *chartView = new QChartView(this);
	build();
	win = new NewQtGuiClass;
	connect(win, SIGNAL(sendsignal(QString)), this, SLOT(getData(QString)));
	//connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(OnTestButtonClick()));
	connect(ui.openFile, SIGNAL(clicked()), this, SLOT(OnOpenFileButtonClick()));
	connect(ui.deleteItem, SIGNAL(clicked()), this, SLOT(removeItems()));
	//connect(ui.paintObj, SIGNAL(clicked()), this, SLOT(paintObj()));
	connect(ui.paintPoint, SIGNAL(clicked()), this, SLOT(paintPoint()));
	connect(ui.open, SIGNAL(clicked()), this, SLOT(OnOpenButtonClick()));
	connect(ui.changeRange, SIGNAL(clicked()), this, SLOT(changeRange()));
	connect(ui.clearAll, SIGNAL(clicked()), this, SLOT(clearAll()));
}

bool QtPairProject::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui.widget && event->type() == QEvent::Paint)
		widgetPaint();

	return QWidget::eventFilter(obj, event);
}

void QtPairProject::widgetPaint()
{
	QPainter painter(ui.widget);

	painter.drawImage(0, offset, image);
	//painter.drawPixmap(0, 0, width(), height(), pmap);



	painter.setRenderHint(QPainter::Antialiasing, true);
	int pointx = 20, pointy = wide - 20 + offset;
	int pointxx = length / 2, pointyy = wide / 2 + offset;
	int width = length - 20 - pointx, height = wide - 40;
	painter.drawRect(5, 5 + offset, length - 10, wide - 10);
	

	QPen penDegree;
	penDegree.setColor(Qt::green);
	penDegree.setWidth(2);
	painter.setPen(penDegree);
	painter.drawLine(pointx, pointyy, width + pointx, pointyy);
	painter.drawLine(pointxx, pointy - height, pointxx, pointy);
	//x轴刻度线
	double xStep = (double)(x_max - x_min) / x_times;
	
	for (int i = 0; i < x_times; i++) {
		painter.drawLine(pointx + (i + 1)*width / x_times, pointyy, pointx + (i + 1)*width / x_times, pointyy + 4);
		//painter.drawText(pointx + (i + 0.75)*width / x_times,
		//	pointyy + 12, QString::number((int)(x_min + xStep * (i + 1))));
	}
	
	//y轴刻度线
	double yStep = (double)(y_max - y_min) / y_times;
	
	for (int i = 0; i < y_times; i++) {
		painter.drawLine(pointxx, pointy - (i + 1)*height / y_times,
			pointxx - 4, pointy - (i + 1)*height / y_times);
		//painter.drawText(pointxx - 20, pointy - (i + 0.85)*height / y_times,
		//	QString::number((int)(y_min + yStep * (i + 1))));
	}
	

	penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter.setPen(penDegree);

	painter.drawText(pointx + (-1 + 0.85)*width / x_times,
		pointyy + 12, QString::number((int)(x_min + xStep * (-1 + 1))));
	painter.drawText(pointxx - 20, pointy - (-1 + 0.95)*height / y_times,
		QString::number((int)(y_min + yStep * (-1 + 1))));
	painter.drawText(pointx + (x_times - 0.85)*width / x_times,
		pointyy + 12, QString::number((int)(x_min + xStep * (x_times))));
	painter.drawText(pointxx - 20, pointy - (y_times - 1 + 0.85)*height / y_times,
		QString::number((int)(y_min + yStep * (y_times))));

	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].getState() == 0) {
			continue;
		}
		char c = lines[i].getC();
		double x1 = lines[i].getX1();
		double x2 = lines[i].getX2();
		double y1 = lines[i].getY1();
		double y2 = lines[i].getY2();
		if (c == 'L') {
			PaintLine(&painter, (double)x1, (double)y1, (double)x2, (double)y2);
		}
		else if (c == 'R') {
			PaintRay(&painter, (double)x1, (double)y1, (double)x2, (double)y2);
		}
		else if (c == 'S') {
			PaintSegment(&painter, (double)x1, (double)y1, (double)x2, (double)y2);
		}
	}
	for (int i = 0; i < circles.size(); i++) {
		if (circles[i].getState() == 0) {
			continue;
		}
		PaintCircle(&painter, (double)circles[i].getX(), (double)circles[i].getY(), (double)circles[i].getR());
	}
	for (int i = 0; i < points.size(); i++) {
		PaintPoint(&painter, points[i].x, points[i].y);
	}
}

void QtPairProject::OnOpenFileButtonClick() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("text(*.txt)"));
	std::string s = fileName.toLocal8Bit().data();
	//qDebug() << s.length();
	if (s.length() == 0) {
		return;
	}
	FILE *fp;
	fp = fopen(s.c_str(), "r");
	
	fseek(fp, 0, SEEK_END);
	int fpLength = ftell(fp);
	rewind(fp);
	if (fpLength == 0) {
		ui.textEdit->setText("this file is empty, please check your input");
		return;
	}

	int n;
	fscanf(fp, "%d", &n);
	for (int i = 0; i < n; i++) {
		char c;
		c = fgetc(fp);
		if (c == EOF) {
			ui.textEdit->setText("your input is less than the n");
			return;
		}
		fscanf(fp, " %c ", &c);
		if (c == 'C') {
			int x, y, r;
			fscanf(fp, "%d %d %d", &x, &y, &r);
			if (r <= 0) {
				ui.textEdit->setText("r is not bigger than 0, please check your input");
				return;
			}
			if (x < -100000 || x > 100000 || y < -100000 || y > 100000 || r > 100000) {
				ui.textEdit->setText("your input is not in the range, please check your input");
				return;
			}
			addGuiCircle(x, y, r);
		}
		else if (c == 'L' || c == 'S' || c == 'R') {
			int x1, y1, x2, y2;
			fscanf(fp, "%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 < -100000 || x1 > 100000 || y1 < -100000 || y1 > 100000) {
				ui.textEdit->setText("your input is not in the range, please check your input");
				return;
			}
			if (x2 < -100000 || x2 > 100000 || y2 < -100000 || y2 > 100000) {
				ui.textEdit->setText("your input is not in the range, please check your input");
				return;
			}
			addGuiLines(x1, y1, x2, y2, c);
		}
		else {
			ui.textEdit->setText("your input format is wrong, please check your input"); 
			return;
		}
	}
	char c;
	c = fgetc(fp);
	if (c != EOF && c != '\n') {
		ui.textEdit->setText("your input is bigger than the n");
		return;
	}
	ui.textEdit->setText("successfully read the file's data");
}

void QtPairProject::OnOpenButtonClick() {
	win->show();
	//this->hide();
}

void QtPairProject::getData(QString data) {
	this->show();
	//ui.textEdit->setText(data);
	//qDebug() << data;
	std::stringstream sstream;
	std::string s = data.toStdString();
	sstream << s;
	char c;
	sstream >> c;
	if (c == 'N') {
		//qDebug() << c;
		;
	}
	else if (c == 'C') {
		int x, y, r;
		sstream >> x;
		sstream >> y;
		sstream >> r;
		//qDebug() << x;
		//qDebug() << y;
		//qDebug() << r;
		
		if (r <= 0) {
			ui.textEdit->setText("r is not bigger than 0, please check your input");
			return;
		}
		if (x < -100000 || x > 100000 || y < -100000 || y > 100000 || r > 100000) {
			ui.textEdit->setText("your input is not in the range, please check your input");
			return;
		}
		addGuiCircle(x, y, r);
	}
	else if (c == 'L' || c == 'S' || c == 'R') {
		int x1, y1, x2, y2;
		sstream >> x1;
		sstream >> y1;
		sstream >> x2;
		sstream >> y2;
		
		if (x1 < -100000 || x1 > 100000 || y1 < -100000 || y1 > 100000) {
			ui.textEdit->setText("your input is not in the range, please check your input");
			return;
		}
		if (x2 < -100000 || x2 > 100000 || y2 < -100000 || y2 > 100000) {
			ui.textEdit->setText("your input is not in the range, please check your input");
			return;
		}
		addGuiLines(x1, y1, x2, y2, c);
	}
	ui.textEdit->setText("successfully read the input data");

}

void QtPairProject::OnTestButtonClick() {
	addGuiCircle(5, 5, 1);
	addGuiLines(2, 4, 3, 4, 'R');
}

void QtPairProject::build() {
	image = QImage(length, wide, QImage::Format_RGB32); 
	QColor backColor = qRgb(255, 255, 255); 
	image.fill(backColor);
}

void QtPairProject::remove(QPainter *painter) {
	QPen pen;
	pen.setWidth(100000);
	painter->setCompositionMode(QPainter::CompositionMode_Clear);
	painter->setPen(pen);                       
	painter->drawPoint(wide / 2, length / 2);
	painter->setCompositionMode(QPainter::CompositionMode_DestinationOver);
	pen.setWidth(2);
	painter->setPen(pen);
}

double QtPairProject::transferX(double x) {
	int pointx = 20;
	int width = length - 20 - pointx;
	double kx = (double)width / (x_max - x_min );
	return pointx + kx * (x - x_min);
}

double QtPairProject::transferY(double y) {
	int pointy = wide - 20;
	int height = wide - 40;
	double ky = (double)height / (y_max - y_min );
	return pointy - (y - y_min) * ky + offset;
}

double QtPairProject::lengthX() {
	return (double)(x_max - x_min) / x_times;
}

double QtPairProject::lengthY() {
	return (double)(y_max - y_min) / y_times;
}

void QtPairProject::PaintPoint(QPainter *painter, double x, double y) {
	QPen penDegree;
	penDegree.setColor(Qt::blue);
	penDegree.setWidth(6);
	painter->setPen(penDegree);
	if (x > x_max || x < x_min || y > y_max || y < y_min) {
		//return;
		;
	}
	painter->drawPoint(transferX(x), transferY(y));
	//penDegree.setColor(Qt::black);
	penDegree.setWidth(2);
	painter->setPen(penDegree);
}

void QtPairProject::PaintLine(QPainter *painter, double x1, double y1, double x2, double y2) {
	double y3, y4;
	if (x1 == x2) {
		painter->drawLine(transferX(x1), transferY(y_min), transferX(x2), transferY(y_max));
		return;
	}
	else {
		y3 = (x_min * y1 - x_min * y2 + x1 * y2 - x2 * y1) / (x1 - x2);
		y4 = (x_max * y1 - x_max * y2 + x1 * y2 - x2 * y1) / (x1 - x2);
	}
	painter->drawLine(transferX(x_min), transferY(y3), transferX(x_max), transferY(y4));
}

void QtPairProject::PaintSegment(QPainter *painter, double x1, double y1, double x2, double y2) {
	painter->drawLine(transferX(x1), transferY(y1), transferX(x2), transferY(y2));
}

void QtPairProject::PaintRay(QPainter *painter, double x1, double y1, double x2, double y2) {
	double y3, y4;
	if (x1 == x2) {
		if (y1 < y2) {
			painter->drawLine(transferX(x1), transferY(y1), transferX(x2), transferY(y_max));
		}
		else {
			painter->drawLine(transferX(x1), transferY(y1), transferX(x2), transferY(y_min));
		}
		return;
	}
	else {
		y3 = (x_min * y1 - x_min * y2 + x1 * y2 - x2 * y1) / (x1 - x2);
		y4 = (x_max * y1 - x_max * y2 + x1 * y2 - x2 * y1) / (x1 - x2);
	}
	if (x1 < x2) {
		painter->drawLine(transferX(x1), transferY(y1), transferX(x_max), transferY(y4));
	}
	else {
		painter->drawLine(transferX(x1), transferY(y1), transferX(x_min), transferY(y3));
	}
}

void QtPairProject::PaintCircle(QPainter *painter, double x, double y, double r) {
	if (r < 0) {
		return;
	}
	double a, b, c, d;
	a = transferX(x - r);
	b = transferY(y - r);
	c = 2 * r * (transferX(1) - transferX(0));
	d = 2 * r * (transferY(1) - transferY(0));
	painter->drawEllipse(a, b, c, d);
}

void QtPairProject::addGuiCircle(int x, int y, int r) {
	circles.push_back(Circle((double)x, (double)y, (double)r, allNum++));
	std::string tmp = "C " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(r);
	QString str = QString::fromStdString(tmp);     
	QListWidgetItem *item = new QListWidgetItem;
	item->setText(str);                    
	ui.listWidget->addItem(item);
	int totalNum = ui.listWidget->count();
	container[totalNum - 1] = std::pair<char, int>('C', circles.size() - 1);
	
}

void QtPairProject::addGuiLines(int x1, int y1, int x2, int y2, char c) {
	lines.push_back(Line((double)x1, (double)y1, (double)x2, (double)y2, c, allNum++));
	std::string s = "a";
	s[0] = c;
	std::string tmp = s + " " + std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(x2) + " " + std::to_string(y2);
	QString str = QString::fromStdString(tmp);     
	QListWidgetItem *item = new QListWidgetItem;
	item->setText(str);                     
	ui.listWidget->addItem(item);
	int totalNum = ui.listWidget->count();
	container[totalNum - 1] = std::pair<char, int>(c, lines.size() - 1);
	/*QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing, true);
	if (c == 'L') {
		PaintLine(&painter, (double)x1, (double)y1, (double)x2, (double)y2);
	}
	else if (c == 'R') {
		PaintRay(&painter, (double)x1, (double)y1, (double)x2, (double)y2);
	}
	else if (c == 'S') {
		PaintSegment(&painter, (double)x1, (double)y1, (double)x2, (double)y2);
	}
	update();*/
}

void QtPairProject::removeItems() {
	//ui.listWidget->setCurrentRow(2);
	//if (ui.listWidget->hasFocus() == 0) {
	//}
	int num = ui.listWidget->currentRow();
	if (num == -1) {
		return;
	}
	char type = container[num].first;
	int order = container[num].second;
	if (type == 'C') {
		circles[order].disable();
	}
	else {
		lines[order].disable();
	}
	QListWidgetItem *item = ui.listWidget->takeItem(ui.listWidget->currentRow());
	delete item;
	int totalNum = ui.listWidget->count();
	for (int i = num; i < totalNum; i++) {
		container[i] = container[i + 1];
	}
	points.clear();
	ui.widget->repaint();
	ui.textEdit->setText("the selected item has been removed");
	//this->hide();
	//this->show();
}

void QtPairProject::paintObj() {
	ui.widget->repaint();
	//this->hide();
	//this->show();
	
}

void QtPairProject::paintPoint() {
	std::stringstream ss;
	int aliveNum = 0;
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].getState() == 1) {
			aliveNum++;
		}
	}
	for (int i = 0; i < circles.size(); i++) {
		if (circles[i].getState() == 1) {
			aliveNum++;
		}
	}
	ss << aliveNum;
	ss << std::endl;
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].getState() == 1) {
			ss << lines[i].to_string();
			ss << std::endl;
		}
	}
	for (int i = 0; i < circles.size(); i++) {
		if (circles[i].getState() == 1) {
			ss << circles[i].to_string();
			ss << std::endl;
		}
	}
	std::vector<std::pair<double, double>> pointss;
	bool sign = false;
	std::string information;
	try {
		getPoints(pointss, ss);
	}
	catch (InputException e) {
		sign = true;
		information = e.what();
		information += "Please change all the wrong datas";
	}
	if (sign) {
		ui.textEdit->setText(information.c_str());
		return;
	}
	std::string s;
	if (pointss.size() == 0) {
		s = "There isn't any points";
	}
	else if (pointss.size() == 1) {
		s = std::to_string(pointss.size()) + " point has been founded";
	}
	else {
		s = std::to_string(pointss.size()) + " points have been founded";
	}
	
	ui.textEdit->setText(s.c_str());
	points.clear();
	for (int i = 0; i < pointss.size(); i++) {
		points.push_back(Point(pointss[i].first, pointss[i].second));
	}
	ui.widget->repaint();
	//this->hide();
	//this->show();
}

void QtPairProject::changeRange() {

	int num = ui.lineEdit->text().toInt();
	ui.lineEdit->clear();
	if (num > 0 && num <= 100000) {
		x_max = y_max = num;
		x_min = y_min = -1 * num;
	}
	ui.textEdit->setText("successfully change the range");
	ui.widget->repaint();
	//this->hide();
	//this->show();
}

void QtPairProject::clearAll() {
	/*for 
	char type = container[num].first;
	int order = container[num].second;
	if (type == 'C') {
		circles[order].disable();
	}
	else {
		lines[order].disable();
	}
	QListWidgetItem *item = ui.listWidget->takeItem(ui.listWidget->currentRow());
	delete item;
	int totalNum = ui.listWidget->count();
	for (int i = num; i < totalNum; i++) {
		container[i] = container[i + 1];
	}*/
	int total_num = ui.listWidget->count();  
	ui.listWidget->setFocus();   
	ui.listWidget->setCurrentRow(0);
	for (int i = 0; i < total_num; i++)
	{  
		QListWidgetItem *item = ui.listWidget->takeItem(ui.listWidget->currentRow());
		delete item;
	}
	for (int i = 0; i < lines.size(); i++) {
		lines[i].disable();
	}
	for (int i = 0; i < circles.size(); i++) {
		circles[i].disable();
	}
	points.clear();
	ui.textEdit->clear();
	ui.widget->repaint();
	ui.textEdit->setText("clear process complete");
	//this->hide();
	//this->show();
}
