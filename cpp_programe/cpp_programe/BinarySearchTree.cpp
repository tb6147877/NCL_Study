//#include <iostream>
//#include <functional>
//#include <utility>
//
//struct Node {
//	int value;//This variable stores data of the node. In the future it will be replaced by a template.
//	Node* left;
//	Node* right;
//	Node* parent;
//	Node() :value{ 0 }, left{ nullptr }, right{ nullptr }, parent{nullptr} {}
//};
//
//class BST {
//private:
//	Node* m_root;
//	void in_order_walk(const std::function<void(Node* node,BST* tree)>& func, Node* node) {
//		if (node!=nullptr)
//		{
//			in_order_walk(func, node->left);
//			func(node,this);
//			in_order_walk(func, node->right);
//		}
//	}
//
//	void post_order_walk(const std::function<void(Node* node, BST* tree)>& func, Node* node) {
//		if (node != nullptr)
//		{
//			post_order_walk(func, node->left);
//			post_order_walk(func, node->right);
//			func(node, this);
//		}
//	}
//
//	Node* minimun(Node* node) {
//		if (node==nullptr)
//		{
//			return node;
//		}
//		while (node->left!=nullptr)
//		{
//			node = node->left;
//		}
//		return node;
//	}
//
//
//
//public:
//	BST() :m_root{ nullptr } {};
//	~BST() { 
//		//terminate_tree(); 
//	}
//
//	Node* getRoot() {
//		return m_root;
//	}
//
//	void insert(const int value) {
//		Node* ptr = new Node;
//		ptr->value = value;
//		Node* x = m_root, * y = nullptr;
//
//		while (x!=nullptr)
//		{
//			y = x;
//			x= (x->value < value)? x->right: x->left;
//		}
//
//		ptr->parent = y;
//		if (y == nullptr) {
//			m_root = ptr;
//			return;
//		}
//
//		//Question:Which piece of code is better, from perspective of compiler and performance?
//		//¢Ù
//		/*if (y->value < value)
//			y->right = ptr;
//		else
//			y->left = ptr;*/
//
//		//¢ÚConfusion:r-value or l-value
//		((y->value < value) ? y->right : y->left) = ptr;
//	}
//
//	void remove(Node* node) {
//		if (node==nullptr)
//		{
//			return;
//		}
//		if (node->left==nullptr)
//		{
//			transplant(node, node->right);
//		}
//		else if (node->right==nullptr)
//		{
//			transplant(node, node->left);
//		}
//		else
//		{
//			Node* t = minimun(node->right);
//			if (t->parent!=node)
//			{
//				transplant(t, t->right);
//				t->right = node->right;
//				t->right->parent = t;
//			}
//			transplant(node, t);
//			t->left = node->left;
//			t->left->parent = t;
//		}
//		delete node;
//	}
//
//	void transplant(Node* ptr_old, Node* ptr_new) {
//		if (ptr_old->parent == nullptr)
//		{
//			m_root = ptr_new;
//			m_root->parent = nullptr;
//			return;
//		}
//		((ptr_old == ptr_old->parent->left) ? ptr_old->parent->left : ptr_old->parent->right) = ptr_new;
//		if (ptr_new != nullptr)
//		{
//			ptr_new->parent = ptr_old->parent;
//		}
//	}
//
//	Node* search(Node* node, const int value) {
//		if (node==nullptr||value==node->value)
//		{
//			return node;
//		}
//		if (value<node->value)
//		{
//			return search(node->left, value);
//		}
//		else {
//			return search(node->right, value);
//		}
//	}
//
//	void print_tree() {
//		std::function<void(Node* node,BST* tree)> printFunc{ [](Node* node,BST* tree) {
//			std::cout << node->value << "\n";
//		} };
//		in_order_walk(printFunc, m_root);
//	}
//
//	void terminate_tree() {
//		if (m_root == nullptr)
//		{
//			std::cout << "This is an empty tree!" << '\n';
//			return;
//		}
//		std::function<void(Node* node, BST* tree)> clearFunc{ [](Node* node,BST* tree) {
//			std::cout << node->value << " end\n";
//			delete node;
//		} };
//		post_order_walk(clearFunc, m_root);
//		m_root = nullptr;
//	}
//
//	int get_most_common_value() {
//		//the first is count, and the second is value
//		std::pair<int, int> max{ 0,0 };
//		std::pair<int, int> cur{ 0,0 };
//		if (m_root != nullptr)
//		{
//			std::function<void(Node* node, BST* tree)> addFunc{ [&](Node* node,BST* tree) {
//				//Could I write if statement like this and help compiler optimize code?
//				//¢Ù
//				/*if (cur.second != node->value)
//				{
//					cur.second = node->value;
//					cur.first = 0;				
//				}*/
//				
//
//				//¢Ú
//				(cur.second != node->value) ? (cur.second = node->value, cur.first = 0) : (0) ;
//
//
//				++cur.first;
//
//				if (max.first<cur.first)
//				{
//					max.first = cur.first;
//					max.second = cur.second;
//				}
//			} };
//			in_order_walk(addFunc, m_root);
//		}
//		else {
//			std::cout << "This is an empty tree!" << '\n';
//		}
//		return max.second;
//	}
//
//	int get_largest_value() {
//		if (m_root==nullptr)
//		{
//			std::cout << "This is an empty tree!" << '\n';
//			return 0;
//		}
//		Node* x = m_root;
//		while (x->right!=nullptr)
//		{
//			x = x->right;
//		}
//		return x->value;
//	}
//
//	int get_sum_of_tree() {
//		int temp{ 0 };
//		if (m_root != nullptr)
//		{
//			std::function<void(Node* node,BST* tree)> addFunc{ [&](Node* node,BST* tree) {
//				temp += node->value;
//			} };
//			in_order_walk(addFunc, m_root);
//		}
//		else {
//			std::cout << "This is an empty tree!"<<'\n';
//		}
//		
//		return temp;
//	}
//};
//
//int main() {
//	BST tree{};
//	tree.insert(88);
//	tree.insert(-10);
//	tree.insert(0);
//	tree.insert(8);
//	tree.insert(100);
//	tree.insert(8); 
//	tree.insert(2);
//	tree.insert(2);
//	tree.insert(2);
//	tree.insert(8);
//	tree.insert(8);
//	tree.insert(63);
//	tree.insert(2);
//	tree.print_tree();
//	std::cout << "-------------------------------------------------------\n";
//	Node* temp =tree.search(tree.getRoot(),7) ;
//
//	tree.remove(temp);
//	std::cout << "-------------------------------------------------------\n";
//	tree.print_tree();
//
//	std::cout << "-------------------------------------------------------\n";
//	/*std::cout << tree.get_sum_of_tree()<<'\n';
//	std::cout << "-------------------------------------------------------\n";
//	std::cout << tree.get_largest_value() << '\n';
//	std::cout << "-------------------------------------------------------\n";
//	std::cout << tree.get_most_common_value() << '\n';*/
//	/*std::cout << "-------------------------------------------------------\n";
//	tree.terminate_tree();
//	std::cout << "-------------------------------------------------------\n";
//	tree.print_tree();*/
//}