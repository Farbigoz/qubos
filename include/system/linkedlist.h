#ifndef SYSTEM_LINKED_LIST_H
#define SYSTEM_LINKED_LIST_H

#include <cstddef>
#include <type_traits>


namespace sys {
	class LinkedListStatic {
	public:
		class Node;
		class Iterator;
		template<typename type>
		class TypedIterator;

	public:
		LinkedListStatic() noexcept
		:
		p_begin(nullptr),
		p_end(nullptr),
		cnt(0)
		{}

		Iterator begin() {
			return Iterator(p_begin);
		}

		template<typename type>
		TypedIterator<type> begin() {
			return TypedIterator<type>(p_begin);
		}

		Iterator end() {
			return Iterator(nullptr);
		}

		bool push_back(Node& data) {
			// Элемент уже в каком-либо списке
			if (data.list != nullptr)
				// Выход
				return false;

			data.list = this;
			data.p_next = nullptr;

			// У списка нет первого элемента
			if (p_begin == nullptr)
			{
				data.p_prev = nullptr;
				p_begin = &data;
			}
			// У списка есть первый элемент
			else
			{
				data.p_prev = p_end;
				p_end->p_next = &data;
			}

			p_end = &data;

			cnt++;
			return true;
		}

		bool push_front(Node& data) {
			// Элемент уже в каком-либо списке
			if (data.list != nullptr)
				// Выход
				return false;

			data.list = this;
			data.p_next = p_begin;
			data.p_prev = nullptr;

			if (p_begin == nullptr)
				p_end = &data;
			else
				p_begin->p_prev = &data;

			p_begin = &data;

			cnt++;
			return true;
		}

		bool remove(Node& data) {
			if (data.list != this)
				return false;

			if (data.p_prev != nullptr)
				data.p_prev->p_next = data.p_next;
			if (data.p_next != nullptr)
				data.p_next->p_prev = data.p_prev;

			if (&data == p_begin)
				p_begin = data.p_next;
			if (&data == p_end)
				p_end = data.p_prev;

			data.p_next = nullptr;
			data.p_prev = nullptr;
			data.list = nullptr;

			cnt--;
			return true;
		}

		inline size_t len() const {
			return cnt;
		}

		inline bool is_empty() const {
			return cnt == 0;
		}

		inline bool has(Node& node) {
			return node.list == this;
		}

	public:
		class Node {
		public:
			Node()
			:
			list(nullptr),
			p_prev(nullptr),
			p_next(nullptr)
			{}

			Node(LinkedListStatic& a_list, bool to_front=false)
			:
			Node()
			{
				if (to_front)
					a_list.push_front(*this);
				else
					a_list.push_back(*this);
			}

			Node(const Node &other) = delete;
			Node(Node &&other) = delete;

			virtual ~Node() {
				if (list == nullptr)
					return;
				list->remove(*this);
			}

			bool in_list() {
				return list != nullptr;
			}

		protected:
			LinkedListStatic *list;
			Node *p_prev;
			Node *p_next;

			friend class LinkedListStatic;
			friend class Iterator;
		};

		class Iterator {
		public:
			explicit Iterator(Node* p_node) noexcept
			:
			p_curr_node(p_node)
			{}

			Iterator& operator=(Node* p_node) {
				this->p_curr_node = p_node;
				return *this;
			}

			Iterator& operator++() {
				if (p_curr_node)
					p_curr_node = p_curr_node->p_next;
				return *this;
			}

			Iterator operator++(int) {
				Iterator iterator = *this;
				++*this;
				return iterator;
			}

			bool operator!=(const Iterator& iterator) {
				return p_curr_node != iterator.p_curr_node;
			}

			virtual Node& operator*() {
				return *p_curr_node;
			}

		protected:
			Node *p_curr_node;
		};

		template <typename type>
		class TypedIterator : public Iterator {
			static_assert(std::is_base_of_v<Node, type>, "Wrong node type.");

		public:
			explicit TypedIterator(Node* p_node)
			:
			Iterator(p_node)
			{}

			type& operator*() override {
				return *dynamic_cast<type*>(p_curr_node);
			}
		};

	private:
		size_t cnt;
		Node *p_begin;
		Node *p_end;
	};

}



// Для чего нужен связный список (потокобезопасный)
// 1. Реестр экземпляров
// 2. Реестр событий








#endif /* SYSTEM_LINKED_LIST_H */