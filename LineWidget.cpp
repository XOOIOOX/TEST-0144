#include "LineWidget.h"

LineWidget::LineWidget(VectorItem& items, QWidget* parent /*= nullptr*/, QGraphicsView* view /*= nullptr*/) : items(items), QWidget(parent), view(view)
{
	installEventFilter(this);
	resize(parent->size());
	calcAreaSize();
	sceneInit();
	update();
}

bool LineWidget::eventFilter(QObject* obj, QEvent* evt)
{
	return false;
}

void LineWidget::sceneInit()
{
	scene = new QGraphicsScene(view->rect(), this);
	view->setScene(scene);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setRenderHints(QPainter::Antialiasing);

	lineItem = new LineItem;
	scene->addItem(lineItem);
}

void LineWidget::updateItems()
{
	lineItem->setHeight(height());
	lineItem->visibleItems = items;				// временно
}

QPointF LineWidget::convertValueToPosition(QPointF point)
{
	return { (point.x() - inputRange.minimum) / (inputRange.maximum - inputRange.minimum) * areaSize.width() + border,
		areaSize.height() - ((point.y() - outputRange.minimum) / (outputRange.maximum - outputRange.minimum)) * areaSize.height() + border };
}

QPointF LineWidget::convertPositionToValue(QPointF point)
{
	return { ((point.x() - border) / areaSize.width()) * (inputRange.maximum - inputRange.minimum) + inputRange.minimum,
		((areaSize.height() - (point.y() - border)) / areaSize.height()) * (outputRange.maximum - outputRange.minimum) + outputRange.minimum };
}

void LineWidget::calcAreaSize()
{
	areaSize = { static_cast<double>(size().width() - border * 2), static_cast<double>(size().height() - border * 2) };
}

void LineWidget::update() { updateItems(); QWidget::update(); }

void LineWidget::setRange(Range inRange, Range outRange)
{
}