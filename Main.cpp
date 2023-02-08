#include <iostream>
#include <memory>
//Smart pointer
//auto_ptr<weak_ptr<unigue_ptr<shared_ptr
class A {
	public:
		A(A & a) = delete;//конструктор копирования не доступен
		A() {
			std::cout << "Constructor A" << std::endl;
		}
		~A() {
			std::cout << "Deconstructor A" << std::endl;
		}
};
class Point {
public:
	Point(int x, int y) : _x(x), _y(y) {
		std::cout << "Point constructor" << std::endl;
	}
	int getX() const {

		return _x;
	}
	~Point() {
		std::cout << "Point deconstructor" << std::endl;
	}
private:
	int _x;
	int _y;
};
//template<typename T>
//auto_ptr{
//T* _ptrObj
//public:
//auto_ptr (T* ptrObj) : _ptrObj(ptrObj){}
template <class T>
class SmartPtr {
	T* _ptr;//есди поле не определенно по умолчанию private
public:
	SmartPtr(T*t) : _ptr(t){ }

	T* operator ->() {//стрелочный оператор если возвращает указатель 
		//то в этом случае на указатель снова вызывается стрелочный оператор
		//рекурсивно до тех пор пока не вернется обьект
		return _ptr;//_ptr->operator-> вызывает сама себя пока не выходит из условия(то есть пока не вернется обьект)
	}
	~SmartPtr() { 
		delete _ptr;
	}
};
//unigue_ptr почти как и любой пользовательский тип 
//можно передавать в параметры фунции по ссылке
void basicFunc(const std::unique_ptr<Point>& p) {//
	std::cout << p->getX() << std::endl;
}
class Parent{};
class Child : public Parent{};
std::shared_ptr<Parent> SomeMethod() {
	Child b;
	std::shared_ptr<Parent> a = std::make_shared<Parent>(b);
	return a;
}

//dynamic_cast<Point*> обычный указатель 
//							 ||
//							 ||
//dynamic_cas smart_pointer \||/
//							 \/
class IVehicle {
public:
	virtual int getSpeed() const = 0;
	virtual const std::string& getType() const = 0;
	virtual ~IVehicle() {}
};
class Car : public IVehicle {
	public:
		Car(int speed) : _speed(speed) {}
		int getSpeed() const override {
			return _speed;
		}
		const std::string& getType() const override{
			return _type;
		}
private:
	 int _speed;
	std::string _type = "Car";
}; 
class Van : public Car{
public:
	Van(int speed) : Car(speed) {}
	
	const std::string& getType() const override {
		return _type;
	}
private:
	std::string _type = "Van";
};

void FuncCar(std::shared_ptr<Car> carPtr) {
	std::cout << "+++++++++++++++++++++" << std::endl;
	std::cout << "Inside funcCar" << std::endl;
	std::cout << carPtr->getSpeed() << std::endl;
	std::cout << carPtr->getType() << std::endl;
}

int main() {
	setlocale(LC_ALL, "Rus");
	
	//A *a = new A();если не удалить указатель delete то деконструктор не отработает
	//std::auto_ptr<A> p(new A());//указатель умный auto_ptr;new = указатель< auto_ptr = лучше неиспользовать
	//std::auto_ptr<A> p2 = p;так нельзя так р остается не определенным
	
	//shared_ptr - имеет контрольный блок в которм по мимо прочегоо лежит счетчик указателей.
	// до тех пор пока живет последний шеред указатель на обьект оьбет класса существует
	//unique_ptr - гарантирует, что только один указатель будет владеть одним обьектом
	
	//std::unique_ptr<A> uptr(new A());
	//std::unique_ptr<Point> pPoint(new Point(5,4));
	
	//std::cout << pPoint->getX() << std::endl;//строки 48 и 49 одно и тоже
	//pPoint.get()->getX();//обращение через метод get() возвращает ссылку -> указатель на Point

	 
	//SmartPtr<Point> sm(new Point(5, 4));
	//std::cout << sm->getX() << std::endl;
	
	//std::unique_ptr<Point> p5 = std::make_unique<Point>(5, 4);//правильный реализация SmartPtr`es
	//p5 = std::make_unique<Point>(5, 4);
	//lv
	//std::shared_ptr<Point> sp1 = std::make_shared<Point>(1, 2);
	//std::shared_ptr<Point> sp2 = sp1;
	//basicFunc(p5);

	std::shared_ptr<Van> v = std::make_shared<Van>(50);
	std::cout << v->getSpeed() << std::endl;
	std::cout << v->getType() << std::endl;
	std::cout <<"+++++++++++++++++++++" << std::endl;
	//std::dynamyc_pointer_cast< new -type>(object to cast)
	std::shared_ptr<Car> c = std::dynamic_pointer_cast<Car>(v);
	std::cout << c->getSpeed() << std::endl;
	std::cout << c->getType() << std::endl;
	FuncCar(c);
	return 0;
}