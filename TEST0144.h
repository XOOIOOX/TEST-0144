#pragma once

#include <QtWidgets/QWidget>
#include "ui_TEST0144.h"
#include "LineWidget.h"
#include "GlobalStructs.h"

class TEST0144 : public QWidget
{
	Q_OBJECT

public:
	TEST0144(QWidget* parent = Q_NULLPTR);
	~TEST0144();

	bool eventFilter(QObject* obj, QEvent* evt);									// ивент-фильтр

private:
	Ui::TEST0144Class ui;
	QGraphicsView* view;											// вьюшка
	LineWidget* lineWidget;
	VectorItem items;
	bool eventResize();
};
