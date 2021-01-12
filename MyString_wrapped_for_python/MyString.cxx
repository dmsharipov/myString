#include <iostream>
#include <initializer_list>
#include <string>

class MyString
{
private:
	char *str;
	size_t len;
	size_t cpct;
	static const size_t npos = -1;

	void change_capacity(size_t size)
	{
	while (cpct <= size)
		cpct += 32;
	}

	bool compare_char(const char* s, size_t pos) const {
			for (int i = 1; i < strlen(s); ++i) {
				if (str[pos + i] != s[i])
					return false;
			}			
		return true;
	}

	bool compare_string(std::string s, size_t pos) const
	{
	for (int i = 1; i < s.length(); ++i) {
		if (str[pos + i] != s[i])
			return false;
	}
	return true;
	}

public:
	#ifdef SWIG 
	%extend 
	{ char __getitem__(int index) 
	{ 
		return $self->get(index); 
	} 
	void __setitem__(int index, char val) 
	{ 
		$self->set(index, val); 
	} 
	char* __str__() 
	{ 
		return (char*)$self->c_str(); 
	} 
	} 
	#endif 

	char& get(uint32_t e) 
	{ 
		return str[e]; 
	} 

	void set(uint32_t pos, char &e) 
	{ 
		str[pos] = e; 
	}

	MyString() {
	cpct = 32;
	str = new char[cpct];
	len = 0;
	}
	MyString(const MyString &s) 
	{
	int i;
	len = s.len;
	cpct = 32;
	change_capacity(len);
	str = new char[cpct];
	for (i = 0; i < len; ++i)
		str[i] = s.str[i];
	str[i] = '\0';
	}

	MyString(const char *s) 
	{
	int i;
	len = strlen(s);
	cpct = 32;
	change_capacity(len);
	str = new char[cpct];
	for (i = 0; i < len; ++i)
		str[i] = s[i];
	str[i] = '\0';
	}

	MyString(const std::initializer_list<char> &il)
	{
	int i = 0;
	len = il.size();
	cpct = 32;
	change_capacity(len);
	str = new char[cpct];
	for (auto &element : il) {
		str[i] = element;
		++i;
	}
	str[i] = '\0';
	}

	MyString(std::string s)
	{
	int i;
	len = s.length();
	cpct = 32;
	change_capacity(len);
	str = new char[cpct];
	for (i = 0; i < len; ++i)
		str[i] = s[i];
	str[i] = '\0';
	}

	MyString(const char s[], int count) 
	{
	int i;
	len = count;
	cpct = 32;
	change_capacity(len);
	str = new char[cpct];
	for (i = 0; i < len; ++i)
		str[i] = s[i];
	str[i] = '\0';
	}

	MyString(int count, const char c)
	{
	int i;
	len = count;
	cpct = 32;
	change_capacity(len);
	str = new char[cpct];
	for (i = 0; i < len; ++i)
		str[i] = c;
	str[i] = '\0';
	}

	~MyString()
	{
	delete[] str;
	}

	MyString operator +(const MyString &s)
	{
	int i;
	size_t buf_len = len + s.len;
	char *data = new char[buf_len + 1];
	for (i = 0; i < len; ++i)
		data[i] = str[i];
	for (i = 0; i < s.len; ++i)
		data[len + i] = s.str[i];
	data[buf_len] = '\0';
	return MyString(data);
	}

	MyString operator +(const char *s)
	{
	int i;
	size_t buf_len = len + strlen(s);
	char *data = new char[buf_len + 1];
	for (i = 0; i < len; ++i)
		data[i] = str[i];
	for (i = 0; i < strlen(s); ++i)
		data[len + i] = s[i];
	data[buf_len] = '\0';
	return MyString(data);
	}

	MyString operator +(std::string s)
	{
	int i;
	size_t buf_len = len + s.length();
	char *data = new char[buf_len + 1];
	for (i = 0; i < len; ++i)
		data[i] = str[i];
	for (i = 0; i < s.length(); ++i)
		data[len + i] = s[i];
	data[buf_len] = '\0';
	return MyString(data);
	}

	MyString& operator +=(const char *s)
	{
	int i;
	size_t buf_len = len + strlen(s);
	change_capacity(buf_len);
	char *data = new char[cpct];
	for (i = 0; i < len; ++i)
		data[i] = str[i];
	for (i = 0; i < strlen(s); ++i)
		data[len + i] = s[i];
	data[buf_len] = '\0';
	delete[] str;
	str = data;
	len = buf_len;
	return *this;
	}

	MyString& operator +=(std::string s)
	{
	int i;
	size_t buf_len = len + s.length();
	change_capacity(buf_len);
	char *data = new char[cpct];
	for (i = 0; i < len; ++i)
		data[i] = str[i];
	for (i = 0; i < s.length(); ++i)
		data[len + i] = s[i];
	data[buf_len] = '\0';
	delete[] str;
	str = data;
	len = buf_len;
	return *this;
	}

	MyString& operator =(const char *s)
	{
	int i;
	len = strlen(s);
	delete[] str;
	cpct = 32;
	change_capacity(len);
	str = new char[cpct];
	for (i = 0; i < len; ++i)
		str[i] = s[i];
	str[i] = '\0';
	return *this;
	}

	MyString& operator =(std::string s)
	{
	int i;
	len = s.length();
	delete[] str;
	cpct = 32;
	change_capacity(len);
	str = new char[cpct];
	for (i = 0; i < len; ++i)
		str[i] = s[i];
	str[i] = '\0';
	return *this;
	}

	MyString& operator =(char c)
	{
	len = 1;
	delete[] str;
	cpct = 32;
	str = new char[2];
	str[0] = c;
	str[1] = '\0';
	return *this;
	}

	char operator [](int n) const
	{
	if (n < 0 || n > len)
		return '\0';
	
	return str[n];
	}

	bool operator >(const MyString &s) const
	{
	int min_len = (len < s.len) ? len : s.len;
	for (int i = 0; i < min_len; ++i) {
		if ((int)this->str[i] > (int)s.str[i])
			return true;
	}
	return false;
	}

	bool operator <(const MyString &s) const
	{
	int min_len = (len < s.len) ? len : s.len;
	for (int i = 0; i < min_len; ++i) {
		if ((int)this->str[i] < (int)s.str[i])
			return true;
	}
	return false;
	}

	bool operator >=(const MyString &s) const
	{
	return !(*this < s);
	}

	bool operator <=(const MyString &s) const
	{
	return !(*this > s);
	}

	bool operator ==(const MyString &s) const
	{
	if (len != s.len)
		return false;
	for (int i = 0; i < len; ++i) {
		if (this->str[i] != s.str[i])
			return false;
	}
	return true;
	}

	bool operator !=(const MyString &s) const
	{
	return !(*this == s);
	}

	const char* c_str(void) const
	{
	return str;
	}

	const char* data(void) const
	{
	char* new_str = new char[len];
	for (int i = 0; i < len; ++i)
		new_str[i] = str[i];
	return new_str;
	}

	size_t length(void) const
	{
	return len;
	}

	size_t size(void) const
	{
	return len;
	}

	bool empty(void) const
	{
	return (len == 0) ? true : false;
	}

	size_t capacity(void) const
	{
	return cpct;
	}

	void shrink_to_fit(void)
	{
	int i;
	cpct = len + 1;
	char *data = new char[cpct];
	for (i = 0; i < len; ++i)
		data[i] = str[i];
	data[i] = '\0';
	delete[] str;
	str = data;
	}

	void clear(void)
	{
	delete[] str;
	cpct = 32;
	str = new char[cpct];
	str[0] = '\0';
	len = 0;
	}

	friend std::ostream& operator <<(std::ostream &ost, MyString &s)
	{
	for (int i = 0; i < s.length(); ++i)
		ost << s[i];
	return ost;
	}

	friend std::istream& operator >>(std::istream &ist, MyString &s)
	{
	char buf[1024];
	ist >> buf;
	s = buf;
	return ist;
	}

	MyString& append(int count, char c)
	{
	int i;
	char *buf = new char[count + 1];
	for (i = 0; i < count; ++i)
		buf[i] = c;
	buf[i] = '\0';
	return (*this += buf);
	}

	MyString& append(const char *s)
	{
	return (*this += s);
	}

	MyString& append(const char *s, int index, size_t count)
	{
	if (index + count > strlen(s))
		return *this;

	int i;
	char *buf = new char[count + 1];
	for (i = 0; i < count; ++i)
		buf[i] = s[index + i];
	buf[i] = '\0';
	return (*this += buf);
	}

	MyString& append(std::string s)
	{
	return (*this += s);
	}

	MyString& append(std::string s, int index, size_t count)
	{
	if (index + count > s.length())
		return *this;

	int i;
	char *buf = new char[count + 1];
	for (i = 0; i < count; ++i)
		buf[i] = s[index + i];
	buf[i] = '\0';
	return (*this += buf);
	}

	MyString& insert(int index, size_t count, char c)
	{
	if (index > len || index < 0)
		return *this;

	int i;
	char *buf = new char[count + 1];
	for (i = 0; i < count; ++i)
		buf[i] = c;
	buf[i] = '\0';
	char *buf_before = new char[index + 1];
	for (i = 0; i < index; i++)
		buf_before[i] = str[i];
	buf_before[i] = '\0';
	char *buf_after = new char[len - index + 1];
	for (i = 0; i < len - index; i++)
		buf_after[i] = str[index + i];
	buf_after[i] = '\0';
	*this = buf_before;
	*this += buf;
	return (*this += buf_after);
	}

	MyString& insert(int index, const char *s)
	{
	if (index > len || index < 0)
		return *this;

	int i;
	char *buf_before = new char[index + 1];
	for (i = 0; i < index; i++)
		buf_before[i] = str[i];
	buf_before[i] = '\0';
	char *buf_after = new char[len - index + 1];
	for (i = 0; i < len - index; i++)
		buf_after[i] = str[index + i];
	buf_after[i] = '\0';
	*this = buf_before;
	*this += s;
	return (*this += buf_after);
	}

	MyString& insert(int index, const char *s, size_t count)
	{
	if (index > len || index < 0 || count > strlen(s))
		return *this;

	int i;
	char *buf = new char[count + 1];
	for (i = 0; i < count; ++i)
		buf[i] = s[i];
	buf[i] = '\0';
	char *buf_before = new char[index + 1];
	for (i = 0; i < index; i++)
		buf_before[i] = str[i];
	buf_before[i] = '\0';
	char *buf_after = new char[len - index + 1];
	for (i = 0; i < len - index; i++)
		buf_after[i] = str[index + i];
	buf_after[i] = '\0';
	*this = buf_before;
	*this += buf;
	return (*this += buf_after);
	}

	MyString& insert(int index, std::string s)
	{
	if (index > len || index < 0)
		return *this;

	int i;
	char *buf_before = new char[index + 1];
	for (i = 0; i < index; i++)
		buf_before[i] = str[i];
	buf_before[i] = '\0';
	char *buf_after = new char[len - index + 1];
	for (i = 0; i < len - index; i++)
		buf_after[i] = str[index + i];
	buf_after[i] = '\0';
	*this = buf_before;
	*this += s;
	return (*this += buf_after);
	}

	MyString& insert(int index, std::string s, size_t count)
	{
	if (index > len || index < 0 || count > s.length())
		return *this;

	int i;
	char *buf = new char[count + 1];
	for (i = 0; i < count; ++i)
		buf[i] = s[i];
	buf[i] = '\0';
	char *buf_before = new char[index + 1];
	for (i = 0; i < index; i++)
		buf_before[i] = str[i];
	buf_before[i] = '\0';
	char *buf_after = new char[len - index + 1];
	for (i = 0; i < len - index; i++)
		buf_after[i] = str[index + i];
	buf_after[i] = '\0';
	*this = buf_before;
	*this += buf;
	return (*this += buf_after);
	}

	MyString& erase(int index, size_t count)
	{
	if (index > len || index < 0 || (count + index) > len)
		return *this;

	int i;
	char *buf_before = new char[index + 1];
	for (i = 0; i < index; i++)
		buf_before[i] = str[i];
	buf_before[i] = '\0';
	char *buf_after = new char[len - index - count + 1];
	for (i = 0; i < len - index - count; i++)
		buf_after[i] = str[index + count + i];
	buf_after[i] = '\0';
	*this = buf_before;
	return (*this += buf_after);
	}

	MyString& replace(int index, size_t count, const char *s)
	{
	this->erase(index, count);
	this->insert(index, s);
	return *this;
	}

	MyString& replace(int index, size_t count, std::string s)
	{
	this->erase(index, count);
	this->insert(index, s);
	return *this;
	}

	const char* substr(int index) const
	{
	if (index > len)
		return "";
	int i;
	char *buf = new char[len - index + 1];
	for (i = 0; i < len - index; ++i)
		buf[i] = str[i + index];
	buf[i] = '\0';
	return buf;
	}
	const char* substr(int index, size_t count) const
	{
	if (index > len || index < 0 || (count + index) > len)
		return "";
	int i;
	char *buf = new char[count + 1];
	for (i = 0; i < count; ++i)
		buf[i] = str[i + index];
	buf[i] = '\0';
	return buf;
	}

	size_t find(const char* s) const
	{
	return find(s, 0);
	}

	size_t find(const char* s, size_t pos) const
	{
	if (pos < 0 || pos > len)
		return npos;

	size_t ret = npos;
	for (; pos <= len - strlen(s); ++pos) {
		if (str[pos] == s[0] && compare_char(s, pos)) {
			ret = pos;
			break;
		}
	}
	return ret;
	}

	size_t find(std::string s) const
	{
	return find(s, 0);
	}

	size_t find(std::string s, size_t pos) const
	{
	if (pos < 0 || pos > len)
		return npos;

	size_t ret = npos;
	for (; pos <= len - s.length(); ++pos) {
		if (str[pos] == s[0] && compare_string(s, pos)) {
			ret = pos;
			break;
		}
	}
	return ret;
	}
};
