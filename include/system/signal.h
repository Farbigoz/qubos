#ifndef SYSTEM_SIGNAL_H
#define SYSTEM_SIGNAL_H

#include <tuple>

#include "system/types.h"
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
		constexpr Signal()
		{}

		void emit(Args... args) {
			for (auto iterator = slot_list.begin<Slot>(); iterator != slot_list.end(); iterator++)
				(*iterator).emit(args...);
		}

		inline bool connect(Slot &slot) {
			return slot_list.push_back(slot);
		}

		inline bool connect(Slot &slot, slot_fn_t fn) {
			slot.set_function(fn);
			return slot_list.push_back(slot);
		}

		inline bool connect(SlotWithCtx &slot, slot_with_ctx_fn_t fn, void *ctx) {
			slot.set_function(fn);
			slot.set_ctx(ctx);
			return slot_list.push_back(slot);
		}

		inline bool disconnect(Slot &slot) {
			return slot_list.remove(slot);
		}

		inline Slot static_slot(slot_fn_t fn) {
			return Slot(*this, fn);
		}

		inline Slot* alloc_slot(slot_fn_t fn) {
			auto* slot = new Slot(*this, fn);
			return slot;
		}

		inline SlotWithCtx static_slot(slot_with_ctx_fn_t fn, void *ctx) {
			return SlotWithCtx(*this, fn, ctx);
		}

		inline SlotWithCtx* alloc_slot(slot_with_ctx_fn_t fn, void *ctx) {
			auto* slot = new SlotWithCtx(*this, fn, ctx);
			return slot;
		}

		inline size_t slot_cnt() {
			return slot_list.len();
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

			inline void set_function(slot_fn_t new_fn) {
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
			SlotWithCtx()
			:
			Slot(),
			fn(nullptr),
			ctx(nullptr)
			{}

			SlotWithCtx(Signal &signal, slot_with_ctx_fn_t fn, void *ctx)
			:
			Slot(signal, nullptr),
			fn(fn),
			ctx(ctx)
			{}

			inline void set_function(slot_with_ctx_fn_t new_fn) {
				fn = new_fn;
			}

			inline void set_ctx(void *new_ctx) {
				ctx = new_ctx;
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