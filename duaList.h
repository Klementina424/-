#pragma once
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

struct Node
{
	string  data;
	Node* prev = NULL;
	Node* next = NULL;
};

class duaList
{
public:
	duaList();
	~duaList();
	void push_back(string);
	void push_front(string);
	void pop_back();
	void pop_front();
	void insert(string, size_t);
	string at(size_t);
	void remove(size_t);
	size_t get_size();
	void print_to_console();
	void clear();
	void set(size_t index, string content);
	bool isEmpty();
	string top();
	void opposite();
	

private:
	Node* head;
	Node* last;
	size_t size;
};
