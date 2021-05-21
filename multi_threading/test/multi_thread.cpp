#include <stdio.h>
#include <thread>
#include <chrono>
#include <string>
#include <iostream>

void GlobalFunc(int n)
{
	using namespace std;
	cout<<"GlobalFunc:"+to_string(n)+"sec to end...\n";
	this_thread::sleep_for(chrono::seconds(n));
	cout<<"GlobalFunc: End\n"<<endl;
}

auto lambda_exp = [](int n)
{
	using namespace std;
	cout << "lambda_exp: " + to_string(n) + "sec to end...\n";
	this_thread::sleep_for(chrono::seconds(n));
	cout<<"lambda_exp: End\n"<<endl;
};

#include <functional>

class Foo{

private:
	int _bias;

public:
	explicit Foo(int b) : _bias(b) {}

	void MemberFunc(int n)
	{
		using namespace std;
		cout<<"MemberFunc:"<<to_string(_bias + n)<<"sec to end...\n";
		this_thread::sleep_for(chrono::seconds(_bias + n));
		cout<<"MemberFunc: End\n"<<endl;
	}


	std::function<void(int)> MemberFunc()
	{
		return ([this](int n){ MemberFunc(n); } );
	}
	
};

int main(){
	using namespace std;

	cout<<"Making several tasks\n";
	thread thr0(GlobalFunc, 2);
	thread thr1(lambda_exp, 3);

	Foo foo(3);

	thread thr2(foo.MemberFunc(), 1);

	cout<<"Waiting for threads end\n";

	thr0.join();
	thr1.join();
	thr2.join();

	cout<<"Process All End\n";

	return(0);
}
