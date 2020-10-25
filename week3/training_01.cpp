#include <iostream>
class SetValue {
private:
	int x, y;
public:
	void x_value(int x) {
		this->x = x;
	}
	void y_value(int y) {
		this->y = y;
	}
	int get_x() {
		return x;
	}
	int get_y() {
		return y;
	}
};

int main() {
	SetValue obj;
	obj.x_value(33);
	obj.y_value(44);

	std::cout << "X = " << obj.get_x() << " ,Y = " << obj.get_y() << std::endl;
	return 0;
}