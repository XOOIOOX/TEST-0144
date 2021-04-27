#include "LineWidget.h"

LineWidget::LineWidget(VectorItem& items, QWidget* parent /*= nullptr*/, QGraphicsView* view /*= nullptr*/) : items(items), QWidget(parent), view(view)
{
	installEventFilter(this);
	resize(parent->size());
	areaSizeCalc();
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
		lineItem->visibleItems.push_back({ static_cast<int>(convertValueToPosition(static_cast<double>(i.begin))),
										 static_cast<int>(convertValueToPosition(static_cast<double>(i.length))) });
	}
}

double LineWidget::convertValueToPosition(double point)
{
	return ((point - inputRange.minimum) / (inputRange.maximum - inputRange.minimum) * areaSize.width() + border) * zoomLevel;
}

double LineWidget::convertPositionToValue(double point)
{
	return ((point / zoomLevel - border) / areaSize.width()) * (inputRange.maximum - inputRange.minimum) + inputRange.minimum;
}

void LineWidget::areaSizeCalc()
{
	areaSize = { static_cast<double>(size().width() - border * 2), static_cast<double>(size().height() - border * 2) };
}

void LineWidget::zoomCalc()
{}

void LineWidget::update() { updateItems(); QWidget::update(); }
void LineWidget::setRange(Range inRange)
{
	inputRange = inRange;
}

void LineWidget::zoomAll()
{
	zoomLevel = 1.0;
	update();
}

void LineWidget::zoomMinus()
{
	zoomLevel /= 2.0;
	update();
}

void LineWidget::zoomPlus()
{
	zoomLevel *= 2.0;
	update();
}