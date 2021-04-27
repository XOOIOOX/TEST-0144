#include "TEST0144.h"
#include <algorithm>

TEST0144::TEST0144(QWidget* parent) : QWidget(parent)
{
	items = { { 0, 10 }, { 20, 10 }, { 40, 10 } };

	ui.setupUi(this);
	view = ui.view;
	lineWidget = new LineWidget(items, ui.widget, view);
	auto [min, max] = std::minmax_element(items.begin(), items.end(), [](const auto& a, const auto& b) { return a.begin < b.begin; });
	lineWidget->setRange({ static_cast<double>(min->begin), static_cast<double>(max->begin + max->length) });
	lineWidget->update();
}