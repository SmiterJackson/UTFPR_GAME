#pragma once

#include "stdafx.h"

template<typename T>
class Lista
{
public:
	Lista():
		first(nullptr), last(nullptr), current(nullptr), size(0)
	{};
	Lista(const Lista<T>& _other):
		first(nullptr), last(nullptr), current(nullptr), size(0)
	{
		unsigned int i = 0U;
		for (i = 0U; i < _other.size; i++)
			this->PushBack(_other[i]->GetInfo());
	};
	~Lista()
	{
		Element<T>* aux = nullptr;
		if (this->first != nullptr)
			this->first->SetPrevious(nullptr);

		while(this->last != nullptr)
		{
			aux = this->last->GetPrevious();
			delete this->last;
			this->last = aux;
		}
	};

	template<typename T_El>
	class Element
	{
	public:
		Element() :
			info(), previous(nullptr), next(nullptr)
		{};
		Element(const T_El* _info) :
			info(*_info), previous(nullptr), next(nullptr)
		{};
		Element(const T_El* _info, Element<T_El>* _previous) :
			info(*_info), previous(_previous), next(nullptr)
		{};
		Element(const T_El* _info, Element<T_El>* _previous, Element<T_El>* _next) :
			info(*_info), previous(_previous), next(_next)
		{};
		~Element()
		{};

		T_El& GetInfo() { return this->info; };
		Element<T_El>* const GetPrevious() { return this->previous; };
		Element<T_El>* const GetNext() { return this->next; };

		void SetInfo(const T_El* _info)
		{
			if (_info == nullptr)
				return;

			this->info = *_info;
		};
		void SetPrevious(Element<T_El>* _previous)
		{
			this->previous = _previous;
		};
		void SetNext(Element<T_El>* _next)
		{
			this->next = _next;
		};

		bool operator!= (Element<T_El>& other)
		{
			return this->GetInfo() != other.GetInfo();
		}

	private:
		T_El info;
		Element<T_El>* previous;
		Element<T_El>* next;
	};
	class iterador
	{
	public:
		iterador() :
			pElement(nullptr), listPosition(0)
		{};
		~iterador()
		{};

		unsigned int& ListPosition() { return this->listPosition; };

		void operator= (Element<T>* _other)
		{
			this->pElement = _other;
		};
		bool operator== (Element<T>* _other)
		{
			return this->pElement == _other;
		};
		bool operator!= (Element<T>* _other)
		{
			return this->pElement != _other;
		};

		iterador& operator++ ()
		{
			this->pElement = this->pElement->GetNext();
			this->listPosition++;
			return (*this);
		}
		iterador& operator++ (int val)
		{
			this->pElement = this->pElement->GetNext();
			this->listPosition++;
			return (*this);
		}

		T& operator* ()
		{
			return this->pElement->GetInfo();
		}
		T*& operator-> ()
		{
			return this->pElement->GetInfo();
		};

	private:
		Element<T>* pElement;
		unsigned int listPosition;
	};

	void const PushBack(const T& item)
	{
		Element<T>* aux = new Element<T>(&item, this->last);

		if(aux == nullptr)
		{
			std::cerr << "Nao foi possivel alocar um novo elemento para a lista: Lista." << std::endl;
			return;
		}

		if (this->first == nullptr)
		{
			this->first = aux;
			this->last = aux;
		}
		else
		{
			this->last->SetNext(aux);
			this->last = aux;
		}

		this->size++;
	};
	void PopBack()
	{
		Element<T>* aux = nullptr;

		if(this->last != nullptr)
		{
			aux = this->last->GetPrevious();

			if (aux != nullptr)
				aux->SetNext(nullptr);

			delete this->last;
			this->last = aux;

			this->size--;
		}
	};
	void PopAt(const unsigned int val)
	{
		unsigned int i = 0U;
		Element<T>* aux = this->first;

		for (i = 0U; i < val && i < this->size; i++)
		{
			if (aux == nullptr)
			{
				std::cerr << "Nao foi possivel remover elemento da lista: Overload unsigned int." << std::endl;
				return;
			}
			aux = aux->GetNext();
		}

		if (aux != nullptr)
		{
			if (aux->GetPrevious() != nullptr)
				aux->GetPrevious()->SetNext(aux->GetNext());

			if (aux->GetNext() != nullptr)
				aux->GetNext()->SetPrevious(aux->GetPrevious());

			if (aux == this->last && aux->GetPrevious() != nullptr)
				this->last = aux->GetPrevious();

			if (aux == this->first && aux->GetNext() != nullptr)
				this->first = aux->GetNext();
		}

		delete aux;
		this->size--;
	};
	void PopAt(iterador it)
	{
		unsigned int i = 0U;
		Element<T>* aux = this->first;

		for (i = 0U; i < it.ListPosition() && i < this->size; i++)
		{
			if (aux == nullptr)
			{
				std::cerr << "Nao foi possivel remover elemento da lista: Overload Iterador." << std::endl;
				return;
			}
			aux = aux->GetNext();
		}

		if (aux != nullptr)
		{
			if (aux->GetPrevious() != nullptr)
				aux->GetPrevious()->SetNext(aux->GetNext());

			if (aux->GetNext() != nullptr)
				aux->GetNext()->SetPrevious(aux->GetPrevious());

			if (aux == this->last && aux->GetPrevious() != nullptr)
				this->last = aux->GetPrevious();

			if (aux == this->first && aux->GetNext() != nullptr)
				this->first = aux->GetNext();
		}

		delete aux;
		this->size--;
	};

	Element<T>* const GetFirst(){ return this->first; };
	Element<T>* const GetLast() { return this->last; };
	Element<T>* const GetCurrent() { return this->current; };

	Element<T>* begin() { return this->first; };
	Element<T>* end() { return this->last->GetNext(); };

	unsigned int GetSize() { return this->size; };

	Element<T>& operator[] (unsigned int val) const
	{
		unsigned int i = 0U;
		Element<T>* aux = this->first;

		for (i = 0U; i < val && i < this->size; i++)
		{
			if (aux == nullptr)
				return *(this->first);
			aux = aux->GetNext();
		}

		return *aux;
	}
	Lista<T>& operator+= (const Lista<T>& _other)
	{
		unsigned int i = 0U;
		for (i = 0U; i < _other.size; i++)
			this->PushBack(_other[i]->GetInfo());
		return *this;
	}
	Lista<T>& operator+= (const T& element)
	{
		this->PushBack(&element);
		return *this;
	}

private:
	void ExchangePointers(Element<T>* p1, Element<T>* p2)
	{
		Element<T>* aux = nullptr;

		if (p1 != nullptr && p2 != nullptr)
		{
			aux = p1->GetPrevious();
			p1->SetPrevious(p2->GetPrevious());
			p2->SetPrevious(aux);

			aux = p1->GetNext();
			p1->SetNext(p2->GetNext());
			p2->SetNext(aux);

			if(p1->GetPrevious() != nullptr)
				p1->GetPrevious()->SetNext(p1);
			if (p1->GetNext() != nullptr)
				p1->GetNext()->SetPrevious(p1);

			if (p2->GetPrevious() != nullptr)
				p2->GetPrevious()->SetNext(p2);
			if (p2->GetNext() != nullptr)
				p2->GetNext()->SetPrevious(p2);
		}
	};
	unsigned int SortPartition(unsigned int start, unsigned int end)
	{
		T* pivotValue = nullptr;
		unsigned int pivotIndex = 0, i = 0;
		unsigned int diff = end - start;

		if (diff > 1)
		{
			this->operator[](start).GetInfo() > this->operator[](end).GetInfo() ? pivotIndex = start : pivotIndex = end;
			ExchangePointers(&this->operator[](pivotIndex), &this->operator[](end));
		}

		pivotValue = &this->operator[](pivotIndex).GetInfo();
		for (i = start, pivotIndex = start; i < end; i++)
		{
			if (this->operator[](i).GetInfo() <= (*pivotValue))
			{
				ExchangePointers(&this->operator[](i), &this->operator[](pivotIndex));
				pivotIndex++;
			}
		}
		if (this->operator[](end) != this->operator[](pivotIndex))
			ExchangePointers(&this->operator[](end), &this->operator[](pivotIndex));

		return pivotIndex;
	};
	void QuickSortRecursion(unsigned int start, unsigned int end)
	{
		unsigned int pivotIndex = 0;

		if (start >= end)
			return;

		pivotIndex = SortPartition(start, end);

		QuickSortRecursion(start, pivotIndex - 1);
		QuickSortRecursion(pivotIndex + 1, end);
	};

public:
	void SortElements()
	{
		if(this->size >= 2)
			QuickSortRecursion(0, this->size - 1);
	};

private:
	Element<T>* first;
	Element<T>* last;
	Element<T>* current;

	unsigned int size;
};