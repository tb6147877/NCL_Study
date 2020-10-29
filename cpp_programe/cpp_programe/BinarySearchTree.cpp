#include <iostream>
#include <functional>
#include <utility>

struct Node {
	int value;//This variable stores data of the node. In the future it will be replaced by a template.
	Node* left;
	Node* right;
	Node* parent;
	Node() :value{ 0 }, left{ nullptr }, right{ nullptr }, parent{nullptr} {}
};

class BST {
private:
	Node* m_root;
	void in_order_walk(const std::function<void(Node* node,BST* tree)>& func, Node* node) {
		if (node!=nullptr)
		{
			in_order_walk(func, node->left);
			func(node,this);
			in_order_walk(func, node->right);
		}
	}

	void post_order_walk(const std::function<void(Node* node, BST* tree)>& func, Node* node) {
		if (node != nullptr)
		{
			post_order_walk(func, node->left);
			post_order_walk(func, node->right);
			func(node, this);
		}
	}

public:
	BST() :m_root{ nullptr } {};
	~BST() { 
		//terminate_tree(); 
	}

	void insert(const int value) {
		Node* ptr = new Node;
		ptr->value = value;
		Node* x = m_root, * y = nullptr;

		while (x!=nullptr)
		{
			y = x;
			x= (x->value < value)? x->right: x->left;
		}

		ptr->parent = y;
		if (y == nullptr) {
			m_root = ptr;
			return;
		}

		//Question:Which piece of code is better, from perspective of compiler and performance?
		//¢Ù
		/*if (y->value < value)
			y->right = ptr;
		else
			y->left = ptr;*/

		//¢ÚConfusion:r-value or l-value
		((y->value < value) ? y->right : y->left) = ptr;
	}

	void remove(Node* node) {}

	void print_tree() {
		std::function<void(Node* node,BST* tree)> printFunc{ [](Node* node,BST* tree) {
			std::cout << node->value << "\n";
		} };
		in_order_walk(printFunc, m_root);
	}

	void terminate_tree() {
		if (m_root == nullptr)
		{
			std::cout << "This is an empty tree!" << '\n';
			return;
		}
		std::function<void(Node* node, BST* tree)> clearFunc{ [](Node* node,BST* tree) {
			std::cout << node->value << " end\n";
			delete node;
		} };
		post_order_walk(clearFunc, m_root);
		m_root = nullptr;
	}

	int get_most_common_value() {
		//the first is count, and the second is value
		std::pair<int, int> max{ 0,0 };
		std::pair<int, int> cur{ 0,0 };
		if (m_root != nullptr)
		{
			std::function<void(Node* node, BST* tree)> addFunc{ [&](Node* node,BST* tree) {
				//Could I write if statement like this and help compiler optimize code?
				//¢Ù
				/*if (cur.second != node->value)
				{
					cur.second = node->value;
					cur.first = 0;				
				}
				*/

				//¢Ú
				(cur.second != node->value) ? (cur.second = node->value,cur.first = 0) :(0) ;
				++cur.first;

				if (max.first<cur.first)
				{
					max.first = cur.first;
					max.second = cur.second;
				}
			} };
			in_order_walk(addFunc, m_root);
		}
		else {
			std::cout << "This is an empty tree!" << '\n';
		}
		return max.second;
	}

	int get_largest_value() {
		if (m_root==nullptr)
		{
			std::cout << "This is an empty tree!" << '\n';
			return 0;
		}
		Node* x = m_root;
		while (x->right!=nullptr)
		{
			x = x->right;
		}
		return x->value;
	}

	int get_sum_of_tree() {
		int temp{ 0 };
		if (m_root != nullptr)
		{
			std::function<void(Node* node,BST* tree)> addFunc{ [&](Node* node,BST* tree) {
				temp += node->value;
			} };
			in_order_walk(addFunc, m_root);
		}
		else {
			std::cout << "This is an empty tree!"<<'\n';
		}
		
		return temp;
	}
};

int main() {
	BST tree{};
	tree.insert(-10);
	tree.insert(0);
	tree.insert(8);
	tree.insert(100);
	tree.insert(8); 
	tree.insert(2);
	tree.insert(2);
	tree.insert(2);
	tree.insert(8);
	tree.insert(8);
	tree.insert(63);
	tree.insert(2);
	tree.print_tree();
	std::cout << "-------------------------------------------------------\n";
	std::cout << tree.get_sum_of_tree()<<'\n';
	std::cout << "-------------------------------------------------------\n";
	std::cout << tree.get_largest_value() << '\n';
	std::cout << "-------------------------------------------------------\n";
	std::cout << tree.get_most_common_value() << '\n';
	/*std::cout << "-------------------------------------------------------\n";
	tree.terminate_tree();
	std::cout << "-------------------------------------------------------\n";
	tree.print_tree();*/
}