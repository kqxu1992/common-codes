#include <stdio.h>
#include <mutex>

using namespace std;
/*
单例模式的优缺点
优点
单例类只有一个实例，节省了内存资源，对于一些需要频繁创建销毁的对象，
使用单例模式可以提高系统性能；

单例模式可以在系统设置全局的访问点，优化和共享数据，
例如前面说的Web应用的页面计数器就可以用单例模式实现计数值的保存。

缺点
单例模式一般没有接口，扩展的话除了修改代码基本上没有其他途径。

*/
/*
饿汉式：在类加载时就完成了初始化，所以类加载比较慢，但获取对象的速度快。
懒汉式：在类加载时不初始化，等到第一次被使用时才初始化。*/


/***单例模式
****模式一：懒汉模式， 编法一：static成员函数new得类内static单例成员(static成员只能调用static成员)
****用双重if判断static单例对象是否需要构建
****在运行时主动调用时，才会去构建对象
***/

template <typename T>
class singleton {
public:

	static singleton* getInstance();
private:
	T m_v;
	singleton() { }
    static singleton* instance;
	static mutex mt;
};
template <typename T>
singleton<T>* singleton<T>::instance = nullptr;
template <typename T>
mutex singleton<T>::mt;


template <typename T>
singleton<T>* singleton<T>::getInstance()
{
	if (instance == NULL) {   //第一个if判可减少加锁的开销
		mt.lock();
		if (instance == NULL) {  //第二个if可消除多线程的带来的错误，在一个if和加锁之间，其它线程已提起调用完该函数
			instance = new singleton();
		}
		mt.unlock();
	}
	return instance;
}

/***单例模式 (推荐)
****模式一：懒汉模式，编法二：static成员函数内构建局部static单例对象(非成员变量)
****函数内的静态属性只会在第一次调用的时候初始化，
****也就保证了SingletonInstance中的对象只会被实例化一次，并且这个过程也是线程安全的。
****在运行时主动调用时，才会去构建对象
***/
template <typename T>
class singleton1 {
public:
	static singleton1* getInstance();
private:
	T m_v;
	singleton1() { }
};
template <typename T>
singleton1<T>* singleton1<T>::getInstance(){
	static singleton1* instance;
	return instance;
}

/***单例模式
****模式二：饿汉模式，装载类时直接初始化，以空间换时间
****类的静态属性只会在第一次加载类的时候初始化，
****也就保证了SingletonInstance中的对象只会被实例化一次，并且这个过程也是线程安全的。
****因为类加载时就实例化了，没有达到Lazy Loading (懒加载) 的效果，如果该实例没被使用，内存就浪费了。
***/
template <typename T>
class singleton2 {
public:
	static singleton2* getInstance();
private:
	T m_v;
	singleton2() { }
	static singleton2* instance;
};
template <typename T>
singleton2<T>* singleton2<T>::instance = new singleton2<T>();
template <typename T>
singleton2<T>* singleton2<T>::getInstance() {
	return instance;
}

int main(int argc, char* argv[])
{
	singleton<int>* sin1 = singleton<int>::getInstance();
	singleton<int>* sin2 = singleton<int>::getInstance();
	if (sin1 == sin2) {
		printf("single instance built successfully\n");
	}
	singleton1<int>* sin11 = singleton1<int>::getInstance();
	singleton1<int>* sin12 = singleton1<int>::getInstance();
	if (sin11 == sin12) {
		printf("single instance1 built successfully\n");
	}

	singleton2<int>* sin21 = singleton2<int>::getInstance();
	singleton2<int>* sin22 = singleton2<int>::getInstance();
	if (sin21 == sin22) {
		printf("single instance2 built successfully\n");
	}
	system("pause");
	return 0;
}