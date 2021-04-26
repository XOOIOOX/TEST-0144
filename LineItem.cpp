#include <QPainter>
#include "LineItem.h"

LineItem::LineItem()
{
}

void LineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	if (!visibleItems.empty())
	{
		painter->setPen({ Qt::NoPen });
		painter->setBrush(Qt::BrushStyle(Qt::SolidPattern));
		painter->setBrush(QColor{ 43, 181, 255 });

		for (auto& i : visibleItems)
		{
			painter->drawRect(QRectF{ QPointF{static_cast<double>( i.begin), 0.0 }, QSizeF{ static_cast<double>(i.length), static_cast<double>(height) } });
		}
	}
}