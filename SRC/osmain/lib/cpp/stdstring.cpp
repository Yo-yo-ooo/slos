#include <inc/String>

using namespace sstd;

inline String::String(){
    size_ = 0;
    buffer_ = new char[1];
    buffer_[0] = '\0';
}

inline String::String(const String& str){
    size_ = str.size_;
    buffer_ = new char[size_ + 1];
    strcpy(buffer_, str.buffer_);
}
inline String::String(const String& str, size_t pos, size_t len)
{
	if (pos > str.size_) {
		size_ = 0;
		buffer_ = new char[1];
		buffer_[0] = '\0';
	} else {
		if (pos + len > str.size_)
			size_ = str.size_ - pos;
		else
			size_ = len;
 
		buffer_ = new char[size_+1];
		const char* p = str.c_str() + pos;
		
		for (size_t i = 0; i < size_; ++i) {
			buffer_[i] = p[i];
		}
		buffer_[size_] = '\0';
	}
}
 
inline String::String(const char* s)
{
	size_ = strlen(s);
	buffer_ = new char[size_+1];
	strcpy(buffer_, s);
}
 
inline String::String(const char* s, size_t n)
{
	if (strlen(s) <= n) {
		size_ = strlen(s);
		buffer_ = new char[size_+1];
		strcpy(buffer_, s);
	} else {
		size_ = n;
		buffer_ = new char[size_+1];
		strncpy(buffer_, s, n);
	}
}
 
inline String::String(size_t n, char c)
{
	size_ = n;
	buffer_ = new char[size_+1];
	memset(buffer_, c, n);
}
 
inline String::~String()
{
	if (buffer_)
		delete [] buffer_;
	size_ = 0;
}
 
inline const char* String::c_str() const
{
	return buffer_;
}
 
inline size_t String::length() const
{
	return size_;
}
 
inline size_t String::size() const
{
	return size_;
}
	
inline char& String::operator [] (size_t pos)
{
	return buffer_[pos];	
}
	
inline const char& String::operator [] (size_t pos) const
{
	if (pos >= size_)
		return '\0';
	else
		return buffer_[pos];	
}
 
 
inline String& String::operator = (const String& str)
{
	if (this->size_ != 0)
		delete [] buffer_;
 
	size_ = str.size_;
	buffer_ = new char[size_+1];
	strcpy(buffer_, str.c_str());
	return *this;
}
 
inline String& String::operator = (const char* s)
{
	if (this->size_ != 0)
		delete [] buffer_;
 
	size_ = strlen(s);
	buffer_ = new char[size_+1];
	strcpy(buffer_, s);
	return *this;
}
 
inline String& String::operator = (char c)
{
	if (this->size_ != 1)
		delete [] buffer_;
 
	size_ = 1;
	buffer_ = new char[size_+1];
	buffer_[0] = c;
	buffer_[size_] = '\0';
	return *this;
}
	
inline String& String::operator += (const String& str)
{
	size_ += str.size_;
	char* data = new char[size_+1];
	strcpy(data, buffer_);
	strcat(data, str.buffer_);
 
	delete [] buffer_;
	buffer_ = data;
	return *this;
}
 
inline String& String::operator += (const char* s)
{
	size_ += strlen(s);
	char* data = new char[size_+1];
	strcpy(data, buffer_);
	strcat(data, s);
 
	delete [] buffer_;
	buffer_ = data;
	return *this;
}
 
inline String& String::operator += (char c)
{
	size_ += 1;
	char* data = new char[size_+1];
	strcpy(data, buffer_);
	strcat(data, &c);
 
	delete [] buffer_;
	buffer_ = data;
	return *this;
}
 
inline String& String::append(const String& str)
{
	*this += str;
	return *this;
}
 
inline String& String::append(const char* s)
{
	*this += s;
	return *this;
}
 
inline String& String::assign(const String& str)
{
	*this = str;
	return *this;
}
	
inline String& String::assign(const char* s)
{
	*this = s;
	return *this;
}
 
inline char& String::at(size_t pos)
{
	return buffer_[pos];
}
	
inline const char& String::at(size_t pos) const
{
	return buffer_[pos];
}
 
inline void String::clear()
{
	delete [] buffer_;
	size_ = 0;
	buffer_ = new char[1];
	buffer_[0] = '\0';
}
	
inline int String::compare(const String& str) const
{
	return strcmp(buffer_, str.buffer_);
}
 
inline int String::compare(const char* s) const
{
	return strcmp(buffer_, s);
}
 
inline const char* String::data() const
{
	return buffer_;
}
	
inline bool String::empty() const
{
	return (size_ == 0);
}
 
static inline String operator + (const String& lhs, const String& rhs)
{
	String str(lhs);
	str += rhs;
	return str;
}
 
static inline String operator + (const String& lhs, const char* rhs)
{
	String str(lhs);
	str += rhs;
	return str;
}
 
static inline String operator + (const char* lhs, const String& rhs)
{
	String str(lhs);
	str += rhs;
	return str;
}
 
static inline String operator + (const String& lhs, char rhs)
{
	String str(lhs);
	str += rhs;
	return str;
}
 
static inline String operator + (char lhs, const String& rhs)
{
	String str(&lhs);
	str += rhs;
	return str;
}
 
static inline bool operator == (const String& lhs, const String& rhs)
{
	return (lhs.compare(rhs) == 0);
}
 
static inline bool operator == (const char* lhs, const String& rhs)
{
	return (rhs.compare(lhs) == 0);
}
 
static inline bool operator == (const String& lhs, const char* rhs)
{
	return (lhs.compare(rhs) == 0);
}
 
static inline bool operator != (const String& lhs, const String& rhs)
{
	return (lhs.compare(rhs) != 0);
}
 
static inline bool operator != (const char* lhs, const String& rhs)
{
	return (rhs.compare(lhs) != 0);
}
 
static inline bool operator != (const String& lhs, const char* rhs)
{
	return (lhs.compare(rhs) != 0);
}
 
static inline bool operator < (const String& lhs, const String& rhs)
{
	return (lhs.compare(rhs) < 0);
}
 
static inline bool operator < (const char* lhs, const String& rhs)
{
	return (rhs.compare(lhs) >= 0);
}
 
static inline bool operator < (const String& lhs, const char* rhs)
{
	return (lhs.compare(rhs) < 0);
}
 
static inline bool operator <= (const String& lhs, const String& rhs)
{
	return (lhs.compare(rhs) <= 0);
}
 
static inline bool operator <= (const char* lhs, const String& rhs)
{
	return (rhs.compare(lhs) > 0);
}
 
static inline bool operator <= (const String& lhs, const char* rhs)
{
	return (lhs.compare(rhs) <= 0);
}
 
static inline bool operator > (const String& lhs, const String& rhs)
{
	return (lhs.compare(rhs) > 0);
}
 
static inline bool operator > (const char* lhs, const String& rhs)
{
	return (rhs.compare(lhs) <= 0);
}
 
static inline bool operator > (const String& lhs, const char* rhs)
{
	return (lhs.compare(rhs) > 0);
}
 
static inline bool operator >= (const String& lhs, const String& rhs)
{
	return (lhs.compare(rhs) >= 0);
}
 
static inline bool operator >= (const char* lhs, const String& rhs)
{
	return (rhs.compare(lhs) < 0);
}
 
static inline bool operator >= (const String& lhs, const char* rhs)
{
	return (lhs.compare(rhs) >= 0);
}
 
