#ifndef SYSTEM_STRING_H
#define SYSTEM_STRING_H


namespace sys {
	class string_buff_custom {
	public:
		string_buff_custom(char *buff, size_t buff_size) : pbuff(buff), buff_size(buff_size)
		{}

		inline char * get_buff() {
			return pbuff;
		}

		inline size_t get_buff_size() const {
			return buff_size;
		}

	private:
		char *pbuff;
		size_t buff_size;
	};

	template<size_t SIZE>
	class string_buff : public string_buff_custom {
	public:
		string_buff() : string_buff_custom(buff, SIZE), buff{'\0'}
		{}

	private:
		char buff[SIZE];
	};

}


#endif /* SYSTEM_STRING_H */