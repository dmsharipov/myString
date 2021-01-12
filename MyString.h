#ifndef _MYSTRING_H_
#define _MYSTRING_H_
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

	void change_capacity(size_t size);
	bool compare_char(const char* s, size_t pos) const;
	bool compare_string(std::string s, size_t pos) const;

public:
	MyString();
	MyString(const MyString &s);
	MyString(const char *s);
	MyString(const std::initializer_list<char> &il);
	MyString(std::string s);
	MyString(const char s[], int count);
	MyString(int count, const char c);
	~MyString();

	MyString operator +(const MyString &s);
	MyString operator +(const char *s);
	MyString operator +(std::string s);

	MyString& operator +=(const char *s);
	MyString& operator +=(std::string s);

	MyString& operator =(const char *s);
	MyString& operator =(std::string s);
	MyString& operator =(char c);

	char operator [](int n) const;

	bool operator >(const MyString &s) const;
	bool operator <(const MyString &s) const;
	bool operator >=(const MyString &s) const;
	bool operator <=(const MyString &s) const;
	bool operator ==(const MyString &s) const;
	bool operator !=(const MyString &s) const;

	const char* c_str(void) const;
	const char* data(void) const;
	size_t length(void) const;
	size_t size(void) const;
	bool empty(void) const;
	size_t capacity(void) const;
	void shrink_to_fit(void);
	void clear(void);

	friend std::ostream& operator <<(std::ostream &ost, MyString &s);
	friend std::istream& operator >>(std::istream &ist, MyString &s);

	MyString& append(int count, char c);
	MyString& append(const char *s);
	MyString& append(const char *s, int index, size_t count);
	MyString& append(std::string s);
	MyString& append(std::string s, int index, size_t count);

	MyString& insert(int index, size_t count, char c);
	MyString& insert(int index, const char *s);
	MyString& insert(int index, const char *s, size_t count);
	MyString& insert(int index, std::string s);
	MyString& insert(int index, std::string s, size_t count);

	MyString& erase(int index, size_t count);

	MyString& replace(int index, size_t count, const char *s);
	MyString& replace(int index, size_t count, std::string s);

	const char* substr(int index) const;
	const char* substr(int index, size_t count) const;

	size_t find(const char* s) const;
	size_t find(const char* s, size_t pos) const;
	size_t find(std::string s) const;
	size_t find(std::string s, size_t pos) const;
};

#endif _MYSTRING_H_