#include "TEST0144.h"
#include <algorithm>
#include <iostream>

TEST0144::TEST0144(QWidget* parent) : QWidget(parent)
{
	std::srand(static_cast<uint32>(std::time(nullptr)));

	for (int i = 0; i < 4; ++i)
	{
		items.clear();

		for (int j = 0, pos = 0, len = 0; j < 2000; ++j)
		{
			items.push_back({ pos, len });
			pos = static_cast<int>((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 10.0) + (pos + len);
			len = static_cast<int>((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 10.0 + 1.0);
		}

		manyItems.push_back(items);
	}

	ui.setupUi(this);
	installEventFilter(this);

	view = ui.view;
	lineWidget = new LineWidget(items, ui.widget, view);
	auto [min, max] = std::minmax_element(items.begin(), items.end(), [](const auto& a, const auto& b) { return a.begin < b.begin; });
	lineWidget->setRange({ static_cast<double>(min->begin), static_cast<double>(max->begin + max->length) });
	lineWidget->zoomAll();
}

TEST0144::~TEST0144() {}

bool TEST0144::eventFilter(QObject* obj, QEvent* evt)
{
	if (obj == this)
	{
		switch (evt->type())
		{
			case QEvent::Resize: { return eventResize(); }
			default: { return false; }
		}
	}
	else { return false; }
}

bool TEST0144::eventResize()
{
	lineWidget->changeRectSlot(rect());
	return true;
}