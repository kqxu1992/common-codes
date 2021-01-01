#include <stdio.h>
#include <mutex>

using namespace std;
/*
����ģʽ����ȱ��
�ŵ�
������ֻ��һ��ʵ������ʡ���ڴ���Դ������һЩ��ҪƵ���������ٵĶ���
ʹ�õ���ģʽ�������ϵͳ���ܣ�

����ģʽ������ϵͳ����ȫ�ֵķ��ʵ㣬�Ż��͹������ݣ�
����ǰ��˵��WebӦ�õ�ҳ��������Ϳ����õ���ģʽʵ�ּ���ֵ�ı��档

ȱ��
����ģʽһ��û�нӿڣ���չ�Ļ������޸Ĵ��������û������;����

*/
/*
����ʽ���������ʱ������˳�ʼ������������رȽ���������ȡ������ٶȿ졣
����ʽ���������ʱ����ʼ�����ȵ���һ�α�ʹ��ʱ�ų�ʼ����*/


/***����ģʽ
****ģʽһ������ģʽ�� �෨һ��static��Ա����new������static������Ա(static��Աֻ�ܵ���static��Ա)
****��˫��if�ж�static���������Ƿ���Ҫ����
****������ʱ��������ʱ���Ż�ȥ��������
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
	if (instance == NULL) {   //��һ��if�пɼ��ټ����Ŀ���
		mt.lock();
		if (instance == NULL) {  //�ڶ���if���������̵߳Ĵ����Ĵ�����һ��if�ͼ���֮�䣬�����߳������������ú���
			instance = new singleton();
		}
		mt.unlock();
	}
	return instance;
}

/***����ģʽ (�Ƽ�)
****ģʽһ������ģʽ���෨����static��Ա�����ڹ����ֲ�static��������(�ǳ�Ա����)
****�����ڵľ�̬����ֻ���ڵ�һ�ε��õ�ʱ���ʼ����
****Ҳ�ͱ�֤��SingletonInstance�еĶ���ֻ�ᱻʵ����һ�Σ������������Ҳ���̰߳�ȫ�ġ�
****������ʱ��������ʱ���Ż�ȥ��������
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

/***����ģʽ
****ģʽ��������ģʽ��װ����ʱֱ�ӳ�ʼ�����Կռ任ʱ��
****��ľ�̬����ֻ���ڵ�һ�μ������ʱ���ʼ����
****Ҳ�ͱ�֤��SingletonInstance�еĶ���ֻ�ᱻʵ����һ�Σ������������Ҳ���̰߳�ȫ�ġ�
****��Ϊ�����ʱ��ʵ�����ˣ�û�дﵽLazy Loading (������) ��Ч���������ʵ��û��ʹ�ã��ڴ���˷��ˡ�
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