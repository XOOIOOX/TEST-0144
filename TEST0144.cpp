#include "TEST0144.h"
#include <algorithm>

TEST0144::TEST0144(QWidget* parent) : QWidget(parent)
{
	std::srand(static_cast<uint32>(std::time(nullptr)));

	for (int i = 0, pos = 0, len = 0; i < 200000; ++i)
	{
		pos = static_cast<int>((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 20) + (pos + len);
		len = static_cast<int>((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 100);
		items.push_back({ pos, len });
	}

	ui.setupUi(this);
	view = ui.view;
	lineWidget = new LineWidget(items, ui.widget, view);
	auto [min, max] = std::minmax_element(items.begin(), items.end(), [](const auto& a, const auto& b) { return a.begin < b.begin; });
	lineWidget->setRange({ static_cast<double>(min->begin), static_cast<double>(max->begin + max->length) });
	lineWidget->zoomAll();
}