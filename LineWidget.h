#pragma once
#include <QWidget>
#include <QGraphicsView>

class LineWidget : public QWidget
{
	Q_OBJECT
public:
	LineWidget(QWidget* parent = nullptr, QGraphicsView* view = nullptr);
	bool eventFilter(QObject* obj, QEvent* evt);
private:

};

