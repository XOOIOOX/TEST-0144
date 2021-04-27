#include <QPainter>
#include <iostream>
#include "LineItem.h"

LineItem::LineItem() {}

LineItem::~LineItem() {}

void LineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	if (!visibleItems.empty())
	{
		painter->setPen({ Qt::NoPen });
		painter->setBrush(Qt::BrushStyle(Qt::SolidPattern));
		painter->setBrush(QColor{ 43, 181, 255 });

		for (auto& i : visibleItems)
		{
			painter->drawRect(QRectF{ QPointF{ static_cast<double>(i.begin), border }, QSizeF{ static_cast<double>(i.length), lineHeight - (border * 2.0) } });
		}
	}
}

void LineItem::setHeight(double height) { lineHeight = height; }
void LineItem::setBorder(double border) { LineItem::border = border; }