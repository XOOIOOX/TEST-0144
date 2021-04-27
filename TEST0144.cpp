#include "TEST0144.h"
#include <algorithm>
#include <iostream>

TEST0144::TEST0144(QWidget* parent) : QWidget(parent)
{
	std::srand(static_cast<uint32>(std::time(nullptr)));

	for (int i = 0; i < numWidgets; ++i)
	{
		items.clear();

		for (int j = 0, pos = 0, len = 0; j < numItems; ++j)
		{
			items.push_back({ pos, len });
			pos = static_cast<int>((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 10.0) + (pos + len);
			len = static_cast<int>((static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)) * 10.0 + 1.0);
		}

		manyItems.push_back(items);
		widgets.emplace_back(new QWidget(this));
		widgets.back()->resize({ size().width(), size().height() / numWidgets });
		widgets.back()->move(widgets.back()->pos().x(), size().height() / numWidgets * i);
	}

	for (auto& i : widgets) { views.emplace_back(new QGraphicsView(i.get())); }

	for (int i = 0; i < numWidgets; ++i)
	{
		lineWidgets.emplace_back(new LineWidget(manyItems[i], widgets[i].get(), views[i].get()));
		auto [min, max] = std::minmax_element(manyItems[i].begin(), manyItems[i].end(), [](const auto& a, const auto& b) { return a.begin < b.begin; });
		lineWidgets.back()->setRange({ static_cast<double>(min->begin), static_cast<double>(max->begin + max->length) });
		lineWidgets.back()->zoomAll();
	}

	ui.setupUi(this);
	installEventFilter(this);
}

TEST0144::~TEST0144() { std::cout << "TEST dest" << std::endl; }

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
	for (int i = 0; i < numWidgets; ++i)
	{
		widgets[i]->move(widgets[i]->pos().x(), size().height() / numWidgets * i);
		QRect lineWidgetRect{ rect().topLeft().x(), rect().topLeft().y() + i * (size().height() / numWidgets), width(), height() / numWidgets };
		lineWidgets[i]->changeRectSlot(lineWidgetRect);
	}
	return true;
}