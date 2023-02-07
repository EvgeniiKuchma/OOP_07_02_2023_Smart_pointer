#include <iostream>
#include <memory>
//Smart pointer
//auto_ptr<weak_ptr<unigue_ptr<shared_ptr
class A {
	public:
		A(A & a) = delete;//����������� ����������� �� ��������
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
	T* _ptr;//���� ���� �� ����������� �� ��������� private
public:
	SmartPtr(T*t) : _ptr(t){ }

	T* operator ->() {//���������� �������� ���� ���������� ��������� 
		//�� � ���� ������ �� ��������� ����� ���������� ���������� ��������
		//���������� �� ��� ��� ���� �� �������� ������
		return _ptr;//_ptr->operator-> �������� ���� ���� ���� �� ������� �� �������(�� ���� ���� �� �������� ������)
	}
	~SmartPtr() { 
		delete _ptr;
	}
};
//unigue_ptr ����� ��� � ����� ���������������� ��� 
//����� ���������� � ��������� ������ �� ������
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

//dynamic_cast<Point*> ������� ��������� 
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
	
	//A *a = new A();���� �� ������� ��������� delete �� ������������� �� ����������
	//std::auto_ptr<A> p(new A());//��������� ����� auto_ptr;new = ���������< auto_ptr = ����� ��������������
	//std::auto_ptr<A> p2 = p;��� ������ ��� � �������� �� ������������
	
	//shared_ptr - ����� ����������� ���� � ������ �� ���� �������� ����� ������� ����������.
	// �� ��� ��� ���� ����� ��������� ����� ��������� �� ������ ����� ������ ����������
	//unique_ptr - �����������, ��� ������ ���� ��������� ����� ������� ����� ��������
	
	//std::unique_ptr<A> uptr(new A());
	//std::unique_ptr<Point> pPoint(new Point(5,4));
	
	//std::cout << pPoint->getX() << std::endl;//������ 48 � 49 ���� � ����
	//pPoint.get()->getX();//��������� ����� ����� get() ���������� ������ -> ��������� �� Point

	 
	//SmartPtr<Point> sm(new Point(5, 4));
	//std::cout << sm->getX() << std::endl;
	
	//std::unique_ptr<Point> p5 = std::make_unique<Point>(5, 4);//���������� ���������� SmartPtr`es
	//p5 = std::make_unique<Point>(5, 4);
	//
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