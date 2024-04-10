constexpr int STK_MAX = 1000;

class Stack
{
	int _top;
	char buf[STK_MAX];
public:
	// constructs this Stack
	Stack() {}
	// adds c to the top of this Stack
	void push(char c)
	{
		if(!isFull()) {
			
		}
	}
	// removes and returns the top character of this Stack
	char pop();
	// peeks at the top char and returns it without removing
	char top();
	// return true if this stack is empty
	bool isEmpty();
	// return true if this stack is full
	bool isFull();
};

// pushes all the characters from string line onto the Stack stk
void push_all(Stack & stk, string line);
// pops characters from stk and prints to cout
// all chars will be on the same line without any extra spaces
void pop_all(Stack & stk);
