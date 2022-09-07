#pragma once

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

	template<typename ElT>
	class Element
	{
	public:
		Element() :
			info(), previous(nullptr), next(nullptr)
		{};
		Element(const ElT* _info) :
			info(*_info), previous(nullptr), next(nullptr)
		{};
		Element(const ElT* _info, Element<ElT>* _previous) :
			info(*_info), previous(_previous), next(nullptr)
		{};
		Element(const ElT* _info, Element<ElT>* _previous, Element<ElT>* _next) :
			info(*_info), previous(_previous), next(_next)
		{};
		~Element()
		{};

		ElT* const GetInfo() { return &this->info; };
		Element<ElT>* const GetPrevious() { return this->previous; };
		Element<ElT>* const GetNext() { return this->next; };

		void SetInfo(const ElT* _info)
		{
			if (_info == nullptr)
				return;

			this->info = *_info;
		};
		void SetPrevious(Element<ElT>* _previous)
		{
			this->previous = _previous;
		};
		void SetNext(Element<ElT>* _next)
		{
			this->next = _next;
		};

	private:
		ElT info;
		Element<ElT>* previous;
		Element<ElT>* next;
	};

	Element<T>* const GetFirst() 
	{ 
		return this->first; 
	};
	Element<T>* const GetLast()
	{
		return this->last;
	};
	Element<T>* const GetCurrent() 
	{ 
		return this->current; 
	};

	unsigned int GetSize() { return this->size; };

	void const PushBack(const T* item)
	{
		Element<T>* aux = new Element<T>(item, this->last, this->first);

		if(aux == nullptr)
		{
			std::cerr << "Nao foi possivel alocar um novo elemento para a lista: Lista." << std::endl;
			return;
		}

		if (this->first == nullptr)
		{
			this->first = aux;
			this->last = aux;

			this->first->SetNext(this->last);
			this->last->SetPrevious(this->first);
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
		Element<T>* aux = nullptr;
		if(this->last != nullptr)
		{
			aux = this->last->GetPrevious();
			aux->SetNext(this->first);
			delete this->last;
			this->last = aux;
			this->first->SetPrevious(this->last);
			size--;
		}
	};

	Element<T>* operator[] (unsigned int val) const
	{
		unsigned int i = 0U;
		Element<T>* aux = this->first;

		for (i = 0U; i < val; i++)
		{
			if (i >= this->size || aux == nullptr)
				return nullptr;
			aux = aux->GetNext();
		}

		return aux;
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
	Element<T>* first;
	Element<T>* last;
	Element<T>* current;

	unsigned int size;
};