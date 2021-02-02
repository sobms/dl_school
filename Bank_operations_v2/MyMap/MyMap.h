#pragma once
namespace Bank_operations {
	
	template <class K, class P>
	class map_it;

	template <class K, class P>
	struct MyPair {
		K first;
		P second;
		MyPair(K f, P s) : first(f), second(s) {};
		MyPair(const MyPair& p) : first(p.first), second(p.second) {};
		MyPair* copy() const {
			return new MyPair(*this);
		}
	};

	template <class K, class P>
	struct Node {
		MyPair<K, P>* info;
		Node* left;
		Node* rigth;
		Node* parent;
	};

	template <class K, class P>
	class My_Map {
		friend class map_it <K, P>;
	protected:
		Node<K, P>* root;
		Node<K, P>* search_next(Node<K, P>* ptr);
		void bypass(Node<K, P>* ptr);
	public:
		My_Map() : root(nullptr) {} //+

		~My_Map();//+
		My_Map(const My_Map<K, P>& lst);
		My_Map(My_Map<K, P>&& second);
		My_Map<K, P>& operator = (const My_Map<K, P>& second);
		My_Map<K, P>& operator = (My_Map<K, P>&& second);
		bool operator != (const My_Map<K, P>& second) const;

		int insert(MyPair<K, P>* pair);//+
		bool empty() const;//+
		void erase(K key);//+
		map_it<K, P> find(K key) const;//+

		typedef map_it<K, P> Iterator;
		Iterator begin() const; //+
		Iterator end() const; //+
	};

	template <class K, class P>
	class map_it {
	private:
		My_Map<K, P>* tree;
		Node<K, P>* ptr;
	public:
		map_it(My_Map<K, P>* a) : tree(a), ptr(a->root) {} //инициализирующий конструктор
		const map_it<K, P> operator ++ (int) { // поиск следующего и переход к нему
			ptr = tree->search_next(ptr);
			return *this;
		}
		MyPair<K, P>* operator * () const {
			return this->ptr->info;
		}
		bool operator != (const map_it<K, P>& it) const {

			if ((ptr != it.ptr) || (tree != it.tree)) {
				return true;
			}
			else return false;
		}
		bool operator == (const map_it<K, P>& it) const {
			if ((ptr == it.ptr) && (tree == it.tree)) {
				return true;
			}
			else return false;
		}
		void set_ptr(Node<K, P>* ptr) {
			this->ptr = ptr;
		}
	};


	template <class K, class P>
	Node<K, P>* My_Map<K, P>::search_next(Node<K, P>* ptr) {
		if (ptr->rigth) {
			ptr = ptr->rigth;
			while (ptr->left) {
				ptr = ptr->left;
			}
			return ptr;
		}

		else if (ptr->parent) {
			Node<K, P>* x = ptr;
			ptr = x->parent;
			while ((ptr->parent) && (x == ptr->rigth)) {
				x = ptr;
				ptr = x->parent;
			}
			if (ptr->left == x) {
				return ptr;
			}
		}
		return nullptr;
	}


	template <class K, class P>
	map_it<K, P> My_Map<K, P>::begin() const {	// поиск минимального в дереве
		map_it<K, P> it (const_cast<My_Map<K, P>*>(this));
		Node<K, P>* ptr = root;
		if (ptr != nullptr) {
			while (ptr->left) {
				ptr = ptr->left;
			}
		}
		it.set_ptr(ptr);
		return it;
	}

	template <class K, class P>
	map_it<K, P> My_Map<K, P>::end() const {
		map_it<K, P> it(const_cast<My_Map<K, P>*>(this));
		it.set_ptr(nullptr);
		return it;
	}
	template <class K, class P>
	bool My_Map<K, P>::empty() const {
		if (this->root) {
			return false;
		}
		else {
			return true;
		}
	}
	template <class K, class P>
	int My_Map<K,P>::insert(MyPair<K, P>* pair) {
		Node<K, P>* node = new Node<K, P>;
		node->info = new MyPair<K, P>(*pair);
		node->left = nullptr;
		node->rigth = nullptr;
		node->parent = nullptr;
		Node<K, P>* ptr = root, *par = nullptr;
		while (ptr) {
			if (ptr->info->first > pair->first) {
				par = ptr;
				ptr = ptr->left;
			}
			else if (ptr->info->first < pair->first) {
				par = ptr;
				ptr = ptr->rigth;
			} 
			else {
			return 0;
			}
		}
		if (!par) {
			root = node;
			return 1;
		}
		if (pair->first > par->info->first) {
			par->rigth = node;
			node->parent = par;
		}
		else {
			par->left = node;
			node->parent = par;
		}
		return 1;
	}
	template <class K, class P>
	map_it<K, P> My_Map<K,P>::find(K key) const{
		Node<K, P>* ptr = root;
		map_it<K, P> it(const_cast<My_Map<K, P>*>(this));
		while (ptr) {
			if (ptr->info->first < key) {
				ptr = ptr->rigth;
			}
			else if (ptr->info->first > key) {
				ptr = ptr->left;
			}
			else {
				it.set_ptr(ptr);
				return it;
			}
		}
		it.set_ptr(nullptr);
		return it;
	}
	
	template <class K, class P>
	void My_Map<K, P>::erase(K key) {
		Node<K, P>* ptr = root;
		// поиск нужного узла
		while (ptr) {
			if (ptr->info->first < key) {
				ptr = ptr->rigth;
			}
			else if (ptr->info->first > key) {
				ptr = ptr->left;
			}
			else {
				break;
			}
		}
		Node<K, P>* y, *p, *par;
		if (!ptr) {
			throw std::exception("Element don't exist!");
			return;
		}
		
		else {
			// выбор реально удаляемого элемента
			if ((!ptr->left)  || (!ptr->rigth)) {
				y = ptr;
			}
			else {
				y = My_Map<K, P>::search_next(ptr);
			}
			// определение потомка удаляемого элемента, он 1
			if (y->left) {
				p = y->left;
			}
			else {
				p = y->rigth;
			}
			// определение родителя
			par = y->parent;
			// связь потомок-родитель 
			if (p) {
				p->parent = par;
			}
			// нет родителя -> удаляется корень
			if (!par) {
				root = p;
			}
			// есть родитель-> устанавливаем связь родитель--потомок
			else if (par) {
				if (par->left == y) {
					par->left = p;
				}
				else {
					par->rigth = p;
				}
			}
			// удаляем элемент и копируем данные
			if (y != ptr) {
				delete ptr->info;
				ptr->info = y->info->copy();
			}
			delete y->info;
		}
	}
	template <class K, class P>
	void My_Map<K, P>::bypass(Node<K, P>* ptr) {
		while (ptr) {
			bypass(ptr->left);
			bypass(ptr->rigth);
			delete(ptr);
			ptr = nullptr;
		}
	}
	template <class K, class P>
	My_Map<K,P>::~My_Map() {
		My_Map<K, P>::bypass(root);
	}
	template <class K, class P>
	My_Map<K, P>::My_Map(const My_Map<K, P>& map) {
		Iterator it = map.My_Map<K, P>::begin();

		for (; it != map.My_Map<K, P>::end(); it++) {
			MyPair<K, P>* data_copy = new MyPair<K, P>(*(*it));
			My_Map<K, P>::insert(data_copy);
		}
	}
	template <class K, class P>
	My_Map<K, P>::My_Map(My_Map<K, P>&& second) {
		Iterator it = My_Map<K, P>::begin();
		for (; it != My_Map<K, P>::end(); it++) {
			delete (*it);
		}

		root = second.root;
	}

	template <class K, class P>
	My_Map<K, P>& My_Map<K, P>::operator = (My_Map<K, P>&& second) {
		Iterator it(My_Map<K, P>::begin());
		for (; it != My_Map<K, P>::end(); it++) {
			delete (*it);
		}

		root = second.root;
		return *this;
	}

	template <class K, class P>
	My_Map<K, P>& My_Map<K, P>::operator = (const My_Map<K, P>& second) {
		Iterator it(My_Map<K, P>::begin());
		for (; it != My_Map<K, P>::end(); it++) {
			delete (*it);
		}

		for (it = second.My_Map<K, P>::begin(); it != second.My_Map<K, P>::end(); it++) {
			MyPair<K, P>* data_copy = new MyPair<K,P>(*(*it));
			My_Map<K, P>::insert(data_copy);
		}
		return *this;
	}
	template <class K, class P>
	bool My_Map<K, P>::operator != (const My_Map<K, P>& second) const{
		return this->root != second.root;
	}
}
