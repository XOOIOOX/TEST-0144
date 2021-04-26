#include "LineWidget.h"

LineWidget::LineWidget(QWidget* parent /*= nullptr*/, QGraphicsView* view /*= nullptr*/)
{
	installEventFilter(this);
}

bool LineWidget::eventFilter(QObject* obj, QEvent* evt)
{
	return false;
}