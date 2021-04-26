#pragma once

#include <QGraphicsRectItem>
#include "GlobalStructs.h"

class LineItem : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	LineItem();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
	VectorItem visibleItems;
	void setHeight(int height);

private:
	int lineHeight{ 0 };
};
