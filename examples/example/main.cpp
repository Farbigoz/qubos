#include "iostream"
#include "system/interface/pin.h"
#include "system/interface/adc.h"
#include "system/interface/dac.h"
#include "system/interface/dma.h"
#include "system/interface/can.h"
#include "system/interface/uart.h"
#include "system/interface/onewire.h"
#include "system/interface/spi.h"
#include "system/interface/i2c.h"
#include "system/interface/fs.h"
#include "system/interface/pll.h"
#include "system/interface/flash.h"
#include "system/interface/tim.h"


extern "C" {
#include "sha1.h"
#include "crc.h"
}


#include <iostream>
using namespace std;



class int_node : public sys::LinkedListStatic::Node {
public:
	explicit int_node(int v)
	:
	Node(),
	value(v)
	{}

	int value;
};



// template <typename T>
// /*static*/ typename LinkedList<T>::Node* LinkedList<T>::m_spRoot = nullptr;

//template <typename T>
//void LinkedList<T>::push_back(T data)
//{
//	Node* pTemp = GetNode(data);
//	if (!GetRootNode())
//	{
//		GetRootNode() = pTemp;
//	}
//	else
//	{
//		Node* pCrawler = GetRootNode();
//		while (pCrawler->pNext)
//		{
//			pCrawler = pCrawler->pNext;
//		}
//
//		pCrawler->pNext = pTemp;
//	}
//}

//template <typename T>
//void LinkedList<T>::Traverse()
//{
//	Node* pCrawler = GetRootNode();
//
//	while (pCrawler)
//	{
//		cout << pCrawler->data << " ";
//		pCrawler = pCrawler->pNext;
//	}
//
//	cout << endl;
//}


template <typename... Args>
class fuck {
public:
	typedef void (*handler_t)(Args...);


public:
	void set_handler(handler_t a_h) {
		h = a_h;
	}

	void set_data(Args... args) {
		data = std::tuple<Args...>(args...);
	}

	void call() {
		std::apply(h, data);
	}

private:
	handler_t h;
	std::tuple<Args...> data;
};

void test(uint16_t a, uint32_t b, uint64_t c) {
	std::cout << a + b + c;
}


void test_slot1_fn(int a) {
	cout << "slot1_fn " << a << endl;
}

void test_slot1_dup_fn(int a) {
	cout << "slot1_dup_fn " << a << endl;
}

void test_slot2_fn(float a) {
	cout << "slot2_fn " << a << endl;
}

void test_slot2_dup_fn(float a) {
	cout << "slot2_dup_fn " << a << endl;
}

void test_slot_with_ctx1_fn(void *ctx, int a) {
	cout << "slot_with_ctx1_fn " << ctx << " " << a << endl;
}

void test_slot_with_ctx2_fn(void *ctx, float a) {
	cout << "slot_with_ctx2_fn " << ctx << " " << a << endl;
}

void pin_irq_fn(sys::ipin& pin) {
	cout << "pin irq" << endl;
}


sys::Signal<int> test_signal1;
sys::Signal<float> test_signal2;

decltype(test_signal1)::Slot test_slot1_dup;
decltype(test_signal2)::Slot test_slot2_dup;


int main() {
	if (false) {
		auto test_slot1 = test_signal1.static_slot(test_slot1_fn);
		test_slot1_dup = test_signal1.static_slot(test_slot1_dup_fn);
		auto test_slot_with_ctx1 = test_signal1.static_slot(test_slot_with_ctx1_fn, (void *) 5);
		auto test_slot2 = test_signal2.static_slot(test_slot2_fn);
		test_signal2.connect(test_slot2_dup);
		test_slot2_dup.set_function(test_slot2_dup_fn);
		auto test_slot_with_ctx2 = sys::Signal<float>::SlotWithCtx(test_signal2, test_slot_with_ctx2_fn,
																   (void *) 15);

		test_signal1.emit(1);
		test_signal2.emit(1.5);

		cout << "sizeof(sys::StaticLinkedList::Node) = " << sizeof(sys::LinkedListStatic::Node) << endl;
		cout << "sizeof(test_signal1)                = " << sizeof(test_signal1) << endl;
		cout << "sizeof(test_signal2)                = " << sizeof(test_signal2) << endl;
		cout << "sizeof(test_slot1)                  = " << sizeof(test_slot1) << endl;
		cout << "sizeof(test_slot_with_ctx1)         = " << sizeof(test_slot_with_ctx1) << endl;
	}


	if (false) {
		sys::LinkedListStatic list;
		int_node value1(1);
		int_node value2(2);
		int_node value3(3);

		auto value4 = new int_node(4);

		cout << list.is_empty() << endl;
		cout << list.len() << endl;

		list.push_back(value1);
		list.push_back(value2);
		list.push_front(value3);
		list.remove(value1);
		list.push_back(value1);
		list.push_front(*value4);

		delete value4;

		for (auto iterator = list.begin<int_node>(); iterator != list.end(); iterator++) {
			cout << (*iterator).value << " ";
		}

		cout << endl;

		cout << list.is_empty() << endl;
		cout << list.len() << endl;
	}

	sys::nullpin pin1;

	static auto slot_pin_irq = pin1.signal_irq.static_slot(pin_irq_fn);

	pin1.trig_irq();

	return 0;
}