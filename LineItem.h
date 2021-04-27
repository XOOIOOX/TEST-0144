#pragma once

#include <QGraphicsRectItem>
#include "GlobalStructs.h"

class LineItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	LineItem();
	~LineItem();

	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
	VectorItem visibleItems;
	void setHeight(double height);
	void setBorder(double border);

private:
	double lineHeight{ 0 };
	double border{ 0 };
};
