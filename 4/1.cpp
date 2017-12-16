#include <iostream>

using namespace std;

class ListNotValid {};
class AccessToTheEmptyList {};
class OutOfRange {};

template<typename T>
struct node{
	T data;
	node* next;
	node* prev;	
};
template<typename T>
class List{
	public:

		List()														// Конструктор для инициализации переменных
		{
			current = NULL;																
			head = NULL;   											//Первый элемент		
			tail = NULL;											//Последний элемент
			length = 0;												//Длина списка 
		}

		void push_back(T elem)										//Добавление элемента в конец списка
		{		
			node<T>* current = new node<T>;									//Создаем добавляемый элемент
			current -> data = elem;									//Заполняем элемент
			current -> prev = tail;									//Связываем с предыдущим элементом
			
			
			current -> next = NULL;									//Указываем, что элемент является последним в списке
			if(!head)												//Если head == NULL т.е. current является первым элементом присвоенным к списку, 
				head = current; 									// то указываем, что он же является первым элементом в списке			
			else													//Иначе добавляем в конец списка
				tail -> next = current;
			tail = current;											//Присваиваем статус последнего элемента
			length++;												//Увеличиваем счётчик элементов на один
		}

		void push_front(T elem)										//Добавление элемента в начало списка
		{		
			node<T>* current = new node<T>;							
			current -> data = elem;
			current -> prev = NULL;									//Предыдущего элемента не существует, так как добавляем элемент в начало
			if(!head){												//Если списка ещё нет
				tail = current;
				current -> next = NULL;
			} 
			else{													//Иначе добавляем элемент в начало списка
				current -> next = head;
				head -> prev = current;
			}
			head = current;											//Указываем добавленный элемент, как первый элемент
			
			length++;
		}

		void add(List<T> list)										//Слияние двух списков
		{
			for(node<T> *n = list.getHead(); n != NULL; n = n -> next)
			{
				push_back(n -> data);								//Добавляем все эелементы из передоваемого списка в текущий список
			}
		}

		void printAll()												//Вывод списка
		{
			node<T> *n = new node<T>;
			for(n = head; n != NULL; n = n -> next)
			{
				cout << n -> data << " ";
			}
			cout << endl;
		}

		void printReverseAll()										//Реверсивный вывод
		{
			node<T> *n = new node<T>;
			for(n = tail; n != NULL; n = n -> prev)
			{
				cout << n -> data << " ";
			}
			cout << endl;
		}

		T operator[] (int pos)										//Перегрузка оператора [] для обращения к списке как к массивам
		{
			node<T>* current = getIn(pos);
			if(pos > length-1)										//Если передаваемая позиция не входит диапозон, то выбрасываем исключение
				throw OutOfRange();
			if(current != NULL)										//Если список пуст выбрасываем исключение
				return getIn(pos) -> data;
			else
				throw OutOfRange();
		}



		int size(){													//Размер списка
			return length;
		}

		void erase(T pos)											//Удаление элемента по позиции 
		{
            if(size() <= 1)
            {
                clear();
                return;
            }
			node<T>* deletingElem = getIn(pos);						//getIn находит нужный элемент(функция getIn имеет модификатор доступа private)
			
			node<T>* prevElem = deletingElem -> prev;
			node<T>* nextElem = deletingElem -> next;
			if(nextElem == NULL)									//Если удаляемый элемент является последним в списке
			{
				prevElem -> next = nextElem;
				tail = prevElem;
			}
			else if(prevElem == NULL)								//Если удаляемый элемент является первым в списке
			{
				nextElem -> prev = prevElem;
				head = nextElem;
			}
			else													//В других случаях просто удаляем элемент и соединяем две соседние элементы между собой
			{
				prevElem -> next = nextElem;
				nextElem -> prev = prevElem;
			}

			
			delete deletingElem;
			length--;
		}	



		T front()													//Возвращает первый элемент списка
		{
			if(head != NULL)
				return head -> data;
			else
				throw AccessToTheEmptyList();
		}

		T back()													//Возвращает последний элемент списка
		{
			if(tail != NULL)
				return tail -> data;
			else
				throw AccessToTheEmptyList();
		}

		void clear()												//Удаляет список
		{
			node<T>* n = new node<T>;
			while(head != NULL)										//Перебор всех элементов
			{
				n = head;
				head = head ->  next;
				delete n;
			}
			tail = NULL;
			length = 0;												//Обнуляем счетчик
		}

		node<T>* getHead()											//Геттер для первого элемента списка
		{
			return head;
		}

		node<T>* getTail()											//Геттер для последнего элемента списка
		{
			return tail;
		}




		private:

			node<T>* current;
			node<T>* head;
			node<T>* tail;
			int length;

			node<T>* getIn(int pos){								//Возвращает элемент по позиции. Если элемент не найден функция возвращает NULL 
				node<T> *n = new node<T>;
				int i = 0;

				for(n = head;n != NULL;n = n->next) {
					if(i == pos) {
						return n;
					}
					i++;
				}
				return NULL;
			}
			


	
};

template<typename T>
class Stack : public List<T>
{

    public:

        Stack() : List<T>()
        {}
        void push(T elem)
        {
            List<T>::push_back(elem);
        }

        void pop()
        {
            List<T>::erase(List<T>::size()-1);
        }

        void show()
        {
            List<T>::printAll();
        }
};

template<typename T>
class Queue : public List<T>
{
    public:
        void push(T elem)
        {
            List<T>::push_back(elem);
        }

        void pop()
        {
            List<T>::erase(0);
        }

        void show()
        {
            List<T>::printAll();
        }
};
	

int main() {

	Stack<int> s;
	Queue<int> q;

	for (int i = 0; i < 10; i++) {
		s.push(i);
		s.show();
	}

	for (int i = 0; i < 10; i++) {
		s.pop();
		s.show();
	}

	for (int i = 0; i < 10; i++) {
		q.push(i);
		q.show();
	}

	for (int i = 0; i < 10; i++) {
		q.pop();
		q.show();
	}

	cin.get();
	return 0;
}