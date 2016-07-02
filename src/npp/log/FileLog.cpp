#include "./FileLog.h"
#include "../internal/Format.h"
#include "../OS.h"
#include "../Types.h"
#include "../Unique.h"
#include <fstream>
#include <cerrno>

using npp::FileLog;
using std::string;
using std::ofstream;

FileLog::FileLog(string path) {
  this->fp = npp::make_unique<ofstream>(path, std::ios::out);
}

FileLog::~FileLog() {
  this->fp->close();
}

void FileLog::log(string msg) {
	if (this->fp->is_open())
	{
		*this->fp << msg;
	}
}
