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
	void setRange(Range inRange);															// диапазон входных значений

private:
	QGraphicsScene* scene;																	// сцена
	QGraphicsView* view;																	// вьюшка
	LineItem* lineItem;																		// итем полоски
	VectorItem& items;																		// ссылка на данные полоски
	double border{ 0 };																		// бордюр
	Range inputRange{ 0.0, 0.0 };															// входной диапазон
	QSizeF areaSize{ 0.0, 0.0 };															// размер активной области
	double zoomLevel{ 1.0 };																// уровень приближения

	void sceneInit();
	void updateItems();
	QPointF convertValueToPosition(QPointF point);											// конвертация значения в позицию
	QPointF convertPositionToValue(QPointF point);											// конвертация позиции в значение
	void areaSizeCalc();
	void zoomCalc();
	double fitAll();
};
