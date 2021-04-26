#include "TEST0144.h"

TEST0144::TEST0144(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
	view = ui.view;
	lineWidget = new LineWidget(items, ui.widget, view);
	
	items = { { 0, 10 }, { 20, 10 }, { 40, 10 } };

	lineWidget->update();
}