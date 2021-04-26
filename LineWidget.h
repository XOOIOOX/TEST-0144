#pragma once
#include <QWidget>
#include <QGraphicsView>
#include "LineItem.h"

class LineWidget : public QWidget
{
	Q_OBJECT
public:
	LineWidget(QWidget* parent = nullptr, QGraphicsView* view = nullptr);
	bool eventFilter(QObject* obj, QEvent* evt);
private:
	QGraphicsScene* scene;																	// сцена
	QGraphicsView* view;																	// вьюшка
	LineItem* lineItem;																		// итем полоски
};

