#pragma once
#include "duaList.h"

duaList::duaList()
{
	head = NULL;
	last = NULL;
	size = 0;
}

duaList::~duaList()
{
	while (head)
	{
		last = head->next;
		delete head;
		head = last;
	}
}

void duaList::push_back(string content)
{
	Node* temp = new Node;
	temp->next = NULL;
	temp->data = content;
	if (!this->isEmpty())
	{
		temp->prev = last;
		last->next = temp;
		last = temp;
	}
	else {
		temp->prev = NULL;
		head = last = temp;
	}
	size++;
}

void duaList::push_front(string content)
{
	Node* temp = new Node;
	temp->prev = NULL;
	temp->data = content;
	if (!this->isEmpty())
	{
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	else
	{
		temp->prev = NULL;
		temp->next = NULL;
		head = last = temp;
	}
	size++;
}

void duaList::pop_back()
{
	if (size == 0)
		return;
	if (size == 1)
	{
		delete last;
		last = head = NULL;
		size--;
		return;
	}
	delete last->next;
	last = last->prev;
	last->next = NULL;
	size--;
}

void duaList::pop_front()
{
	if (size == 0)
		return;
	if (size == 1)
	{
		delete head;
		head = last = NULL;
		size--;
		return;
	}
	delete head->prev;
	head->prev = NULL;
	head = head->next;
	size--;
}

void duaList::insert(string content, size_t index)
{
	if ((size == 0 && index == 0) || index >= size)
		throw "Incorrect index.";
	if (index == 0)
	{
		this->push_front(content);
		return;
	}
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	Node* temp = new Node;
	temp->data = content;
	temp->next = cursor;
	temp->prev = cursor->prev;
	cursor->prev = temp;
	temp->prev->next = temp;
	size++;
}

string duaList::at(size_t index)
{
	if (index >= size || index < 0)
		throw "Incorrect index.";
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	return cursor->data;
}

void duaList::remove(size_t index)
{
	if (index >= size || index < 0)
		throw "Incorrect index.";
	if (index == 0)
	{
		this->pop_front();
		return;
	}
	if (index == size - 1)
	{
		this->pop_back();
		return;
	}
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	Node* temp = cursor;
	cursor->prev->next = cursor->next;
	cursor->next->prev = cursor->prev;
	delete temp;
	size--;
}

size_t duaList::get_size()
{
	return size;
}

void duaList::print_to_console()
{
	Node* cursor = head;
	if (head)
	{
		while (cursor->next)
		{
			std::cout << cursor->data << " ";
			cursor = cursor->next;
		}
		std::cout << cursor->data;
		std::cout << std::endl;
	}
	else throw "List is empty.";
}

void duaList::clear()
{
	while (head != NULL)
		this->pop_front();
	head = last = NULL;
}

void duaList::set(size_t index, string content)
{
	if (index >= size || index < 0)
		throw"Incorrect index.";
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	cursor->data = content;
}

bool duaList::isEmpty()
{
	if (head == NULL) return true;
	return false;
}

void duaList::opposite()
{
	if (!head || !head->next)
		return;
	last = head;
	Node* temp = NULL;
	Node* cur = head;
	while (cur != NULL)
	{
		temp = cur->prev;
		cur->prev = cur->next;
		cur->next = temp;
		cur = cur->prev;
	}
	head = temp->prev;
}

string duaList::top()
{
	if (head)
		return head->data;
	else throw "is Empty";
}