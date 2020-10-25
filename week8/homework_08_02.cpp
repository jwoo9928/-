#include<iostream>

class Strategy{
public:
	virtual int doOperation(int n1, int n2) = 0;
};

class Add : public Strategy{
	public:
		int doOperation(int n1, int n2) override{
			return n1 + n2;
		}
};

class Multiply : public Strategy{
	public:
		int doOperation(int n1, int n2) override{
			return n1 * n2;
		}
};

class Substract : public Strategy{
	public:
		int doOperation(int n1, int n2) override {
			return n1 - n2;
		}
};

class Context{
	private:
		Strategy *strategy;

	public:
		Context(Strategy *strategy){
			this->strategy = strategy;
		}
		int executeStrategy(int n1, int n2){
			return strategy->doOperation(n1,n2);
		}
};

int main(){
	Context *context = new Context(new Add());
	std::cout << context->executeStrategy(10,5) << std::endl;
	context = new Context(new Multiply());
	std::cout << context->executeStrategy(10,5) << std::endl;
	context = new Context(new Substract());
	std::cout << context->executeStrategy(10,5) << std::endl;

}