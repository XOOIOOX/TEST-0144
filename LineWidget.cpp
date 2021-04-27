#include <QEvent>
#include <QMouseEvent>
#include <iostream>
#include "LineWidget.h"

LineWidget::LineWidget(VectorItem& items, QWidget* parent /*= nullptr*/, QGraphicsView* view /*= nullptr*/) : items(items), QWidget(parent), view(view), parent(parent)
{
	installEventFilter(this);
	resize(parent->size());
	areaSizeCalc();
	sceneInit();

	connect(&commonBus, &CommonBus::zoomPlusSignal, this, &LineWidget::zoomPlusSlot);
	connect(&commonBus, &CommonBus::zoomMinusSignal, this, &LineWidget::zoomMinusSlot);
	connect(this, &LineWidget::zoomPlusSignal, &commonBus, &CommonBus::zoomPlusSlot);
	connect(this, &LineWidget::zoomMinusSignal, &commonBus, &CommonBus::zoomMinusSlot);

	update();
}

LineWidget::~LineWidget() {}

bool LineWidget::eventFilter(QObject* obj, QEvent* evt)
{
	if (obj == this)
	{
		auto* me = static_cast<QMouseEvent*>(evt);
		auto* we = static_cast<QWheelEvent*>(evt);
		switch (evt->type())
		{
			//case QEvent::MouseButtonPress: { return eventButtonPress(me); }
			//case QEvent::MouseButtonRelease: { return eventButtonRelease(); }
			//case QEvent::MouseButtonDblClick: { return eventButtonDouble(me); }
			//case QEvent::MouseMove& QEvent::HoverEnter: { return eventMoveHover(me); }
			case QEvent::Wheel: { return eventWheel(we); }
			default: { return false; }
		}
	}
	else { return false; }
}

bool LineWidget::eventWheel(QWheelEvent* we)
{
	auto angle = we->angleDelta() / 8 / 15;
	int num{ 0 };
	if (angle.x() != 0) { num = angle.x(); }
	if (angle.y() != 0) { num = angle.y(); }
	if (we->modifiers() & Qt::ControlModifier)
	{
		if (num == 1) { emit zoomPlusSignal(); return true; };
		if (num == -1) { emit zoomMinusSignal(); return true; };
	}

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
	lineItem->setBorder(border);
	lineItem->visibleItems.clear();
	for (auto& i : items)
	{
		auto pos = convertValueToPosition(static_cast<double>(i.begin));
		auto len = convertValueToPosition(static_cast<double>(i.length));
		if (len < 1.0) { len = 1.0; }
		if (pos + len > 0.0 && pos < areaSize.width()) { lineItem->visibleItems.push_back({ static_cast<int>(pos), static_cast<int>(len) }); }
	}

	auto last = std::unique(lineItem->visibleItems.begin(), lineItem->visibleItems.end(), [](const auto& a, const auto& b) { return a.begin == b.begin; });
	lineItem->visibleItems.erase(last, lineItem->visibleItems.end());
}

double LineWidget::convertValueToPosition(double point)
{
	return ((point - inputRange.minimum) / (inputRange.maximum - inputRange.minimum) * areaSize.width()) * zoomLevel;
}

double LineWidget::convertPositionToValue(double point)
{
	return (((point) / zoomLevel) / areaSize.width()) * (inputRange.maximum - inputRange.minimum) + inputRange.minimum;
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

void LineWidget::zoomMinusSlot()
{
	zoomLevel /= zoomMultiplier;
	update();
}

void LineWidget::zoomPlusSlot()
{
	zoomLevel *= zoomMultiplier;
	update();
}

void LineWidget::changeRectSlot(QRect rect)
{
	resize(rect.size());
	parent->resize(rect.size());
	view->resize(rect.size());
	scene->setSceneRect(view->rect());
	areaSizeCalc();
	update();
}