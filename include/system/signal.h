#ifndef SYSTEM_SIGNAL_H
#define SYSTEM_SIGNAL_H

#include <tuple>

#include "system/system.h"
#include "system/linkedlist.h"


namespace sys {
	template <typename... Args>
	class Signal {
	public:
		class Slot;
		class SlotWithCtx;

		typedef void (*slot_fn_t)(Args...);
		typedef void (*slot_with_ctx_fn_t)(void *, Args...);

	public:
		Signal()
		{}

		void emit(Args... args) {
			for (auto iterator = slot_list.begin<Slot>(); iterator != slot_list.end(); iterator++)
				(*iterator).emit(args...);
		}

		bool connect(Slot &slot) {
			return slot_list.push_back(slot);
		}

		bool disconnect(Slot &slot) {
			return slot_list.remove(slot);
		}

		Slot static_slot(slot_fn_t fn) {
			return Slot(*this, fn);
		}

		Slot* alloc_slot(slot_fn_t fn) {
			auto* slot = new Slot(*this, fn);
			return slot;
		}

		SlotWithCtx static_slot(slot_with_ctx_fn_t fn, void *ctx) {
			return SlotWithCtx(*this, fn, ctx);
		}

		SlotWithCtx* alloc_slot(slot_with_ctx_fn_t fn, void *ctx) {
			auto* slot = new SlotWithCtx(*this, fn, ctx);
			return slot;
		}

	public:
		class Slot : public sys::LinkedListStatic::Node {
		public:
			Slot()
			:
			Node(),
			fn(nullptr)
			{}

			Slot(Signal &signal, slot_fn_t fn)
			:
			Node(signal.slot_list, false),
			fn(fn)
			{}

			//void operator()(Signal &signal, slot_fn_t a_fn) {
			//	if (list != nullptr)
			//		list->remove(*this);
			//	signal.slot_list.push_back(*this);
			//	fn = a_fn;
			//}

			//Slot(const Slot& slot) noexcept
			//:
			//Node(slot.list, false),
			//fn(slot.fn)
			//{}

			//Slot(Slot&& slot) noexcept
			//:
			//Node(slot.list, false),
			//fn(slot.fn)
			//{}

			Slot& operator=(Slot&& slot) noexcept {
				if (list != nullptr)
					list->remove(*this);
				if (slot.list != nullptr)
					slot.list->push_back(*this);
				fn = slot.fn;
				return *this;
			}

			void set_function(slot_fn_t new_fn) {
				fn = new_fn;
			}

		protected:
			virtual void emit(Args... args) {
				if (fn != nullptr)
					fn(args...);
			}

		private:
			slot_fn_t fn;
			friend class Signal;
		};

		class SlotWithCtx : public Slot {
		public:
			SlotWithCtx(Signal &signal, slot_with_ctx_fn_t fn, void *ctx)
			:
					Slot(signal, nullptr),
					fn(fn),
					ctx(ctx)
			{}

			void set_function(slot_with_ctx_fn_t new_fn) {
				fn = new_fn;
			}

		protected:
			void emit(Args... args) override {
				if (fn != nullptr)
					fn(ctx, args...);
			}

		protected:
			slot_with_ctx_fn_t fn;
			void *ctx;
			friend class Signal;
		};

	protected:
		sys::LinkedListStatic slot_list;

		friend class Slot;
	};
}


#endif /* SYSTEM_SIGNAL_H */