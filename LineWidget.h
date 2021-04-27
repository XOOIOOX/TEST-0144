#pragma once
#include <QWidget>
#include <QGraphicsView>
#include "GlobalStructs.h"
#include "LineItem.h"

constexpr auto zoomMultiplier{ 1.25 };														// множитель зума

class LineWidget : public QWidget
{
	Q_OBJECT
public:
	LineWidget(VectorItem& items, QWidget* parent = nullptr, QGraphicsView* view = nullptr);
	bool eventFilter(QObject* obj, QEvent* evt);
	void update();
	void setRange(Range inRange);															// диапазон входных значений
	void zoomAll();																			// показать весь диапазон
	void zoomMinus();
	void zoomPlus();

private:
	QGraphicsScene* scene;																	// сцена
	QGraphicsView* view;																	// вьюшка
	LineItem* lineItem;																		// итем полоски
	VectorItem& items;																		// ссылка на данные полоски
	double border{ 0 };																		// бордюр
	Range inputRange{ 0.0, 1.0 };															// входной диапазон
	QSizeF areaSize{ 0.0, 0.0 };															// размер активной области
	double zoomLevel{ 1.0 };																// уровень приближения, 1 = весь диапазон

	void sceneInit();
	void updateItems();
	double convertValueToPosition(double point);											// конвертация значения в позицию
	double convertPositionToValue(double point);											// конвертация позиции в значение
	void areaSizeCalc();
	void zoomCalc();
	bool eventWheel(QWheelEvent* we);														// обработка колеса мыши
};
