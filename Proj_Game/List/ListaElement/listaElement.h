#pragma once

#include "stdafx.h"

template<typename T>
class ListaElement
{
public:
	ListaElement() :
		info(), previous(nullptr), next(nullptr)
	{};
	ListaElement(const T* _info) :
		info(*_info), previous(nullptr), next(nullptr)
	{};
	ListaElement(const T* _info, ListaElement<T>* _previous) :
		info(*_info), previous(_previous), next(nullptr)
	{};
	ListaElement(const T* _info, ListaElement<T>* _previous, ListaElement<T>* _next) :
		info(*_info), previous(_previous), next(_next)
	{};
	~ListaElement()
	{};

	T& GetInfo() { return this->info; };
	ListaElement<T>* const GetPrevious() { return this->previous; };
	ListaElement<T>* const GetNext() { return this->next; };

	void SetInfo(const T* _info)
	{
		if (_info == nullptr)
			return;

		this->info = *_info;
	};
	void SetPrevious(ListaElement<T>* _previous)
	{
		this->previous = _previous;
	};
	void SetNext(ListaElement<T>* _next)
	{
		this->next = _next;
	};

	bool operator!= (ListaElement<T>& other)
	{
		return this->GetInfo() != other.GetInfo();
	}

private:
	T info;
	ListaElement<T>* previous;
	ListaElement<T>* next;
};