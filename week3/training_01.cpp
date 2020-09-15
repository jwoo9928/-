#include <iostream>
class SetValue {
public:
	int x, y;

	void x_value(int a) {
		x = a;
	}
	void y_value(int b) {
		y = b;
	}
};

int main() {
	SetValue obj;
	obj.x_value(33);
	obj.y_value(44);

	std::cout << "X = " << obj.x << " ,Y = " << obj.y << std::endl;
	return 0;
}