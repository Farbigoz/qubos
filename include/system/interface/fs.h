#ifndef SYSTEM_INTERFACE_FS_H
#define SYSTEM_INTERFACE_FS_H

#include "system/system.h"

namespace sys {

class ifs {
public:
	class istat;
	class ifile;
	class idir;

public:
	typedef enum TYPE_T {
		TYPE_FILE,
		TYPE_DIR
	} type_t;

	typedef enum FLAG_T {

	} flag_t;

	typedef enum SEEK_T {
		FS_SEEK_SET,
		FS_SEEK_CUR,
		FS_SEEK_END
	} seek_t;

public:
	virtual result_t init() = 0;

	virtual result_t format() = 0;
	virtual result_t mount() = 0;
	virtual result_t unmount() = 0;

	virtual result_t size(size_t &size) = 0;

	virtual result_t remove(const char *path) = 0;
	virtual result_t rename(const char *old_path, const char *new_path) = 0;
	virtual result_t stat(const char *path, istat&) = 0;
	virtual result_t open(ifile&, const char *path, flag_t) = 0;
	virtual result_t mkdir(const char *path) = 0;
	virtual result_t open(idir&, const char *path) = 0;

public:
	class istat {
	public:
		virtual const char * name() = 0;
		virtual size_t size() = 0;
		virtual type_t type() = 0;
	};

	class ifile {
	public:
		virtual result_t sync() = 0;
		virtual result_t read(size_t &cnt, uint8_t *p_data, size_t size) = 0;
		virtual result_t write(size_t &cnt, const uint8_t *p_data, size_t size) = 0;
		virtual result_t seek(seek_t whence, size_t offset) = 0;
		virtual result_t truncate(size_t offset) = 0;
		virtual result_t tell(size_t &offset) = 0;
		virtual result_t size(size_t &size) = 0;
		virtual result_t close() = 0;

	protected:
		ifile() {}
	};

	class idir {
	public:
		virtual result_t read(istat&) = 0;
		virtual result_t seek(seek_t whence, size_t offset) = 0;
		virtual result_t tell(size_t &offset) = 0;
		virtual result_t close() = 0;
	};


protected:
	ifs() {}
};
}


#endif /* SYSTEM_INTERFACE_FS_H */