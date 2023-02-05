#include <iostream>
class Parent {
public:
	virtual void sleep() {
		std::cout << "Sleep()\n";
	}
	virtual ~Parent() {}//при создании виртуальных функций надо создавать виртуальный диструктор 
};
class Child :public Parent {
public:
	void sleep()override {
		std::cout << "child sleep\n";
	}
	void gotoShchool() {
		std::cout << "goto school()\n";
	}
};
void func(Parent other) {//при передаче указателя пройдет стр.37 файл проходит через конструктор копирования и подменяется
	std::cout << "func\n";
	other.sleep();
}

int main() {
	setlocale(LC_ALL, "Russian");

	Parent parent;
	Child child;

	//up-cast(неявное преоброзование типов разрешено)
	Parent* pPa = &child;//стэк
	Parent* pPa2 = new Child;//куча

	//downcast
	Child* pCh = (Child*)pPa;//C-style cast выполняет первый успешный каст в порядке : const_ cast
																					// static_cast
																					// static_cast->const_cast
																					// reinterpret_cast
																					// reinterpret_cast->const_cast																				// 
																					//
	//если классы наследования в  иерархии не виртуальные то можно кастовать через static_cast 
	Child* pChild = static_cast<Child*>(pPa);

	//downcast UB(undefind behaved(неопределенное поведение))- так делать нельзя
	Child* pCh2 = (Child*)&parent;//сдесь работает но вдругом месте несможет(у обьекта парент нет функций child)
	pPa->sleep();//sleep() - non virtual, child sleep - virtual function
	pCh->sleep();
	pCh2->sleep();//UB
	func(*pPa);

	delete pPa2;
	//static_cast<new_type>(expression) - если кастить классы из разной иерархии то это UB
	int a = 5;
	std::cout << "int: " << a << '\n';
	double b = static_cast<double>(a);//b=(double)a || b=double(a)
	std::cout << "double: " << b << '\n';
	//const_ cast - снимает константность(не сработает с константными методами классов, так как там const *this)
	int c = 6;
	const int* pc = &c;
	//*pc =5;-ошибка
	int* ppc = const_cast<int*>(pc);
	//*ppc = 7;
	std::cout << *ppc << "\n";
	*ppc = 9;
	std::cout << *ppc << ' ' << c << "\n";
	//dynamic_cast<new_type>(expression)- для работы с виртуальными классами ; UB когда касятся классы не находятся в одной иерархии || не виртуальные
	Child* pChild2 = dynamic_cast<Child*>(&parent);//если каст не произойдет то каст указывает на nullptr
	if (pChild2 == nullptr)
		std::cout << "pChild2 is nullptr\n";
	try {
		Child& pchald = dynamic_cast<Child&>(parent);
	}
	catch (std::bad_cast& e) {
		std::cout << "cast parent to child results in the bad_cast" << '\n' << e.what() << '\n';
	}

	return 0;
}