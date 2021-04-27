#pragma once
#include <vector>

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

class LineWidget;

struct Item
{
	int begin{ 0 };
	int length{ 0 };
};

struct Range																			// диапазон
{
	double minimum, maximum;
	double range() { return maximum - minimum; }
	double compress(double input) { return  (input - minimum) / range(); }
	double expand(double input) { return input * range() + minimum; }
	bool inRange(double input) { return input >= minimum && input <= maximum; }
	double toRange(double input) { return input < minimum ? minimum : input > maximum ? maximum : input; }
	double toRange(double input) const { return input < minimum ? minimum : input > maximum ? maximum : input; }
};

template<typename T> using Vector = std::vector<T>;
template<typename T> using Shared = std::shared_ptr<T>;
template<typename T, typename U> auto makeItem(U& data) { return std::make_shared<T>(data); }	// сокращенный make_shared (с параметрами конструтора)
template<typename T> auto makeItem() { return std::make_shared<T>(); }							// сокращенный make_shared (без параметров конструтора)

using VectorInt = Vector<int>;
using VectorItem = Vector<Item>;
using VectorVectorItem = Vector<VectorItem>;
using VectorViewws = Vector<Shared<QGraphicsView>>;
using VectorWidgets = Vector<Shared<QWidget>>;
using VectorLineWidgets = Vector<Shared<LineWidget>>;

