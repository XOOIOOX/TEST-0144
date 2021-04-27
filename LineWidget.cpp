#include "LineWidget.h"

LineWidget::LineWidget(VectorItem& items, QWidget* parent /*= nullptr*/, QGraphicsView* view /*= nullptr*/) : items(items), QWidget(parent), view(view)
{
	installEventFilter(this);
	resize(parent->size());
	areaSizeCalc();
	zoomLevel = fitAll();
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
	lineItem->visibleItems.clear();
	for (auto& i : items)
	{
		lineItem->visibleItems.push_back({ static_cast<int>(convertValueToPosition({ static_cast<double>(i.begin), 0.0 }).x() * zoomLevel),
										 static_cast<int>(convertValueToPosition({ static_cast<double>(i.length), 0.0 }).x() * zoomLevel) });
	}
}

QPointF LineWidget::convertValueToPosition(QPointF point)
{
	return { (point.x() - inputRange.minimum) / (inputRange.maximum - inputRange.minimum) * areaSize.width() + border,
		areaSize.height() + border };
}

QPointF LineWidget::convertPositionToValue(QPointF point)
{
	return { ((point.x() - border) / areaSize.width()) * (inputRange.maximum - inputRange.minimum) + inputRange.minimum,
		areaSize.height() - border };
}

void LineWidget::areaSizeCalc()
{
	areaSize = { static_cast<double>(size().width() - border * 2), static_cast<double>(size().height() - border * 2) };
}

void LineWidget::zoomCalc()
{}

double LineWidget::fitAll()
{
	if (!items.empty())
	{
		auto firstItem = *items.begin();
		auto lastItem = *(items.end() - 1);
		auto length = (lastItem.begin + lastItem.length) - firstItem.begin;
		return length > 0 ? areaSize.width() / static_cast<double>(length) : 1.0;
	}
	else { return 1.0; }
}

void LineWidget::update() { updateItems(); QWidget::update(); }
void LineWidget::setRange(Range inRange) { inputRange = inRange; }