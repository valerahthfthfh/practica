#include <iostream>
#include <string>

using namespace std;

class Context {
public:
	Context() {}
	~Context() {}
};

class AbstractExpression {
public:
	virtual void Interpret(Context& c) = 0;
	virtual ~AbstractExpression() {}
protected:
	AbstractExpression() {}
};

class TerminalExpression : public AbstractExpression {
private:
	string text;
public:
	TerminalExpression(const string& text) {
		this->text = text;
	}

	~TerminalExpression() override {}

	void Interpret(Context& c) override {

		cout << this->text << " TerminalExpression" << endl;
	}
};

class NonterminalExpression : public AbstractExpression {
private:
	AbstractExpression* expression = nullptr;
	int times;
public:
	NonterminalExpression(AbstractExpression* expression, int times) {
		this->expression = expression;
		this->times = times;
	}

	~NonterminalExpression() {
		delete expression;
	}

	void Interpret(Context& c) override {

		for (int i = 0; i < times; i++) {
			this->expression->Interpret(c); // 
		}
	}
};

int main() {

	Context* c = new Context();
	AbstractExpression* TextInput = new TerminalExpression("hello");
	AbstractExpression* NumberAndText = new NonterminalExpression(TextInput, 2);
	NumberAndText->Interpret(*c);
	delete c;
	delete NumberAndText;
}

