#pragma once

#include "../ListaElement/listaElement.h"
#include "../Iterador/iterador.h"

template<typename T>
class Lista
{
public:
	Lista():
		first(nullptr), last(nullptr), size(0)
	{};
	Lista(const Lista<T>& _other):
		first(nullptr), last(nullptr), size(0)
	{
		unsigned int i = 0U;
		for (i = 0U; i < _other.size; i++)
			this->PushBack(_other[i]->GetInfo());
	};
	~Lista()
	{
		ListaElement<T>* aux = nullptr;
		if (this->first != nullptr)
			this->first->SetPrevious(nullptr);

		while(this->last != nullptr)
		{
			aux = this->last->GetPrevious();
			delete this->last;
			this->last = aux;
		}
	};

	class Iterador : public AbstractIterator<T>
	{
	public:
		Iterador():
			AbstractIterator<T>(),
			start(nullptr),
			pElement(nullptr), 
			started(false)
		{};
		Iterador(ListaElement<T>* _start):
			AbstractIterator<T>(),
			start(_start),
			pElement(_start),
			started(false)
		{};
		~Iterador()
		{};

		unsigned long long int& ListPosition() { return this->listPosition; };

		virtual void Next()
		{
			if (this->pElement != nullptr)
			{
				if (this->pElement->GetNext() != nullptr)
				{
					this->pElement = this->pElement->GetNext();
					this->started = true;
				}
			}
		}; 
		virtual void Previous()
		{
			if (this->pElement != nullptr)
			{
				if (this->pElement->GetPrevious() != nullptr)
				{
					this->pElement = this->pElement->GetPrevious();
					this->started = true;
				}
			}
		};
		virtual bool IsDone()
		{
			return (this->pElement == this->start && this->started);
		};
		virtual T& Current()
		{
			return this->pElement->GetInfo();
		};

		void operator= (Iterador& _other)
		{
			this->pElement = _other.pElement;
		};
		void operator= (ListaElement<T>* _other)
		{
			this->pElement = _other;
		};
		bool operator== (Iterador& _other)
		{
			return (this->pElement == _other.pElement && this->started);
		};
		bool operator== (ListaElement<T>* _other)
		{
			return (this->pElement == _other && this->started);
		};
		bool operator!= (Iterador& _other)
		{
			return (this->pElement != _other.pElement || !this->started);
		};
		bool operator!= (ListaElement<T>* _other)
		{
			return (this->pElement != _other || !this->started);
		};

		T& operator* ()
		{
			return this->pElement->GetInfo();
		}
		T*& operator-> ()
		{
			return this->pElement->GetInfo();
		};

		Iterador& operator++ ()
		{
			this->Next();
			this->listPosition++;
			return (*this);
		}
		Iterador& operator++ (int val)
		{
			this->Next();
			this->listPosition++;
			return (*this);
		}
		Iterador& operator-- ()
		{
			this->Previous();
			this->listPosition--;
			return (*this);
		}
		Iterador& operator-- (int val)
		{
			this->Previous();
			this->listPosition--;
			return (*this);
		}

	private:
		const ListaElement<T>* start;
		ListaElement<T>* pElement;
		bool started;
	};

	void const PushBack(const T& item)
	{
		ListaElement<T>* aux = new ListaElement<T>(&item, this->last, this->first);

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
			this->first->SetPrevious(this->last);
		}

		this->size++;
	};
	void PopBack()
	{
		ListaElement<T>* aux = nullptr;

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
		ListaElement<T>* aux = this->first;

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
	void PopAt(Iterador it)
	{
		unsigned int i = 0U;
		ListaElement<T>* aux = this->first;

		for (i = 0U; i < it.ListPosition() && i < this->size; i++)
		{
			if (aux == nullptr)
			{
				std::cerr << "Não foi possível remover o elemento da lista: Overload Iterador." << std::endl;
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

	ListaElement<T>* const GetFirst(){ return this->first; };
	ListaElement<T>* const GetLast() { return this->last; };

	ListaElement<T>* begin() { return this->first; };
	ListaElement<T>* end() { return this->first; };

	unsigned int GetSize() { return this->size; };

	ListaElement<T>& operator[] (unsigned int val) const
	{
		unsigned int i = 0U;
		ListaElement<T>* aux = this->first;

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
	ListaElement<T>* first;
	ListaElement<T>* last;

	unsigned int size;
};