#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

class Point {
private:
	int x, y;

public:
	Point() {
		x = 0;
		y = 0;
	};

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int getX() {
		return x;
	};

	int getY() {
		return y;
	};
};

class MyStack {
private:
	int size_, position_;

public:
	static const int MAX_SIZE = 1000;

	MyStack(int size) {
		if (size > MAX_SIZE) {
			throw std::overflow_error("Too big size of stack");
		}

		size_ = size;
		position_ = 0;
	}

	void push(Point item) {
		if (position_ >= size_) {
			throw std::overflow_error("Stack is full");
		}

		stack[position_++] = item;
	}

	Point pop() {
		if (position_ == 0) {
			throw std::logic_error("Stack is empty");
		}

		Point item = stack[--position_];
		return item;
	}

	bool isEmpty() {
		return position_ == 0;
	}

	Point top() {
		if (position_ == 0) {
			throw std::logic_error("Stack is empty");
		}

		return stack[position_ - 1];
	}

	Point nextToTop() {
		if (position_ < 2) {
			throw std::logic_error("Not enough elements");
		}

		return stack[position_ - 2];
	}

	int size() {
		return position_;
	}

private:
	Point stack[MAX_SIZE];
};

// Поиск квадрата расстония между точками
long getDistance2(Point p1, Point p2) {
	return (p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) +
		(p1.getY() - p2.getY()) * (p1.getY() - p2.getY());
}

// Определение поворота угла
int getDirection(Point p1, Point p2, Point p3) {
	int angle = (p2.getY() - p1.getY()) * (p3.getX() - p2.getX())
		- (p2.getX() - p1.getX()) * (p3.getY() - p2.getY());

	if (angle == 0) {
		//colinear
		return 0;
	}
	else if (angle > 0) {
		//cw
		return 1;
	}
	else {
		//cc
		return 2;
	}
}

// Начальная точка с минимальной координатой Y
Point p0;

// Сортировка по полярному углу
bool comp(Point p1, Point p2) {
	double atanA = atan2(p1.getY() - p0.getY(), p1.getX() - p0.getX());
	double atanB = atan2(p2.getY() - p0.getY(), p2.getX() - p0.getX());

	if (atanA != atanB) {
		return atanA < atanB;
	}
	else {
		return getDistance2(p0, p1) < getDistance2(p0, p2);
	}
}

// Поиск индекса начальной точки с минимальной координатой Y
int getMinPoint(std::vector<Point> points, int count) {
	int minY = points[0].getY();
	int index = 0;

	for (int i = 1; i < count; i++) {
		int curr = points[i].getY();

		if (curr < minY) {
			minY = points[i].getY();
			index = i;
		}
		else if (minY == curr && points[i].getX() < points[index].getX()) {
			minY = points[i].getY();
			index = i;
		}
	}

	return index;
}

MyStack GrahamScan(std::vector<Point> points, int count) {
	// Поиск индекса начальной точки с минимальным значением Y
	int index = getMinPoint(points, count);

	// Смещаем начальную точку в начало 
	Point t = points[index];
	points[index] = points[0];
	points[0] = t;

	p0 = points[0];

	// Сортируем по полярному углу
	std::sort(points.begin() + 1, points.end(), comp);

	int arrSize = 1;
	// Удаляем все точки, лежащие на одной прямой, кроме самой дальней
	for (int i = 1; i < count; i++) {
		while (i < count - 1 && getDirection(p0, points[i], points[i + 1]) == 0)
		{
			i++;
		}

		points[arrSize] = points[i];
		arrSize++;
	}

	MyStack convexHull(arrSize);

	convexHull.push(points[0]);
	convexHull.push(points[1]);
	convexHull.push(points[2]);

	for (int i = 3; i < arrSize; i++)
	{
		while (getDirection(convexHull.nextToTop(), convexHull.top(), points[i]) != 2)
		{
			convexHull.pop();
		}
		convexHull.push(points[i]);
	}

	return convexHull;
}

// Чтение точек из файла
std::vector<Point> getPointsFromFile(std::string path) {
	std::ifstream test;
	std::string line;

	std::vector<Point> points;

	test.open(path);

	if (test.is_open()) {
		std::getline(test, line);

		int count = std::stoi(line.c_str());
		int x, y;

		for (int i = 0; i < count; i++) {
			std::getline(test, line);
			int space_index = line.find(" ");

			x = std::stoi((line.substr(0, space_index)).c_str());
			y = std::stoi((line.substr(space_index, line.length() - 1)).c_str());

			Point p(x, y);
			points.push_back(p);
		}

		test.close();
	}

	return points;
}

// Запись multipoint в файл для формата wkt
void writeMultipoint(std::vector<Point> points, std::string path) {
	std::ofstream answer;

	answer.open(path);

	if (answer.is_open()) {
		std::string line = "MULTIPOINT (";

		for (int i = 0; i < points.size(); i++)
		{
			line += "(" + std::to_string(points[i].getX()) + " " + std::to_string(points[i].getY()) + "), ";
		}

		line = line.erase(line.length() - 2) + ")";

		answer << line << std::endl;

		answer.close();
	}
}

// Запись ответа в файл для формата plain
void writePlainPointsToFile(std::string path, MyStack convexHull, std::string order) {
	std::ofstream answer;
	int size = convexHull.size();

	answer.open(path);

	if (answer.is_open()) {
		answer << convexHull.size() << std::endl;

		if (order._Equal("cc")) {
			MyStack stack(size);
			for (int i = 0; i < size; i++) {
				stack.push(convexHull.pop());
			}

			while (!stack.isEmpty()) {
				Point p = stack.pop();
				answer << p.getX() << " " << p.getY() << std::endl;
			}
		}
		else {
			answer << p0.getX() << " " << p0.getY() << std::endl;

			for (int i = 0; i < size - 1; i++) {
				Point p = convexHull.pop();
				answer << p.getX() << " " << p.getY() << std::endl;
			}
		}

		answer.close();
	}
}

// Запись ответа в файл для формата wkt
void writeWktPointsToFile(std::string path, MyStack convexHull, std::string order) {
	std::ofstream answer;
	int size = convexHull.size();

	answer.open(path, std::ios_base::app);

	if (answer.is_open()) {
		if (order._Equal("cw")) {
			std::string line = "POLYGON ((" + std::to_string(p0.getX())
				+ " " + std::to_string(p0.getY()) + ", ";

			while (!convexHull.isEmpty()) {
				Point point = convexHull.pop();
				line += std::to_string(point.getX()) + " " + std::to_string(point.getY()) + ", ";
			}

			line = line.erase(line.length() - 2) + "))";

			answer << line << std::endl;
		}
		else {
			MyStack stack(size);
			std::string line = "POLYGON ((";

			while (!convexHull.isEmpty()) {
				stack.push(convexHull.pop());
			}

			while (!stack.isEmpty()) {
				Point p = stack.pop();
				line += std::to_string(p.getX()) + " " + std::to_string(p.getY()) + ", ";
			}

			line += std::to_string(p0.getX()) + " " + std::to_string(p0.getY()) + "))";

			answer << line << std::endl;
		}

		answer.close();
	}
}

int main(int argc, char** argv) {
	//if (argc < 5) {
	//	return -1;
	//}

	//std::vector<Point> points = getPointsFromFile(argv[3]);
	//if (points.size() > 0) {
	//	if (std::string(argv[2]) == "wkt") {
	//		writeMultipoint(points, argv[4]);
	//	}

	//	MyStack convexHull = GrahamScan(points, points.size());

	//	if (std::string(argv[2]) == "wkt") {
	//		writeWktPointsToFile(argv[4], convexHull, argv[1]);
	//	}
	//	else if (std::string(argv[2]) == "plain") {
	//		writePlainPointsToFile(argv[4], convexHull, argv[1]);
	//	}
	//}
}
