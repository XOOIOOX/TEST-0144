#pragma once
#include <QWidget>
#include <QGraphicsView>
#include "GlobalStructs.h"
#include "LineItem.h"

class LineWidget : public QWidget
{
	Q_OBJECT
public:
	LineWidget(VectorItem& items, QWidget* parent = nullptr, QGraphicsView* view = nullptr);
	bool eventFilter(QObject* obj, QEvent* evt);
	void update();

private:
	QGraphicsScene* scene;																	// сцена
	QGraphicsView* view;																	// вьюшка
	LineItem* lineItem;																		// итем полоски
	VectorItem& items;																		// ссылка на данные полоски

	void sceneInit();
	void updateItems();
};

