#include "TEST0144.h"

TEST0144::TEST0144(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	view = ui.view;
	lineWidget = new LineWidget(ui.widget, view);
}
