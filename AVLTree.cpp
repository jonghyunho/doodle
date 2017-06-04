#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int MAX(int a, int b) {
	return a >= b ? a : b;
}

struct Node {
	Node* parent;
	Node* left;
	Node* right;
	int key;

	Node(int k)
	: parent(NULL)
	, left(NULL)
	, right(NULL)
	, key(k) {
	}
};

class AVLTree {
private:
	Node* root;

public:
	AVLTree()
	: root(NULL) {
	}

	~AVLTree() {

	}

	Node** getRoot() {
		return &root;
	}

	void addNode(Node* node, int key) {
		if (root == NULL) {
			root = new Node(key);
		} else {
			if (key <= node->key) {
				if (node->left == NULL) {
					node->left = new Node(key);
					node->left->parent = node;

					rebalance(node->parent);
				}
				else {
					addNode(node->left, key);
				}
			}
			else {
				if (node->right == NULL) {
					node->right = new Node(key);
					node->right->parent = node;

					rebalance(node->parent);
				}
				else {
					addNode(node->right, key);
				}
			}
		}
	}

	int deleteNode(Node* node, int key) {
		if (node == NULL) {
			return -1;
		}
		else {
			if (key < node->key) {
				return deleteNode(node->left, key);
			}
			else if (key > node->key) {
				return deleteNode(node->right, key);
			}
			else {
				Node* parent = node->parent;

				if (node->left == NULL && node->right == NULL) {
					if (parent->left == node) {
						parent->left = NULL;
					}
					else {
						parent->right = NULL;
					}

					int key = node->key;
					if (node != NULL) {
						delete node;
						node = NULL;
					}

					rebalance(parent);
					return key;
				}
				else {
					if (node->left != NULL && node->right != NULL) {
						Node* minNode = searchMinNode(node->right);
						int minKey = deleteNode(minNode, minNode->key);
						node->key = minKey;
						return minKey;
					}
					else {
						Node* tempNode;
						if (node->left != NULL) {
							tempNode = node->left;							
						}
						else {
							tempNode = node->right;
						}

						if (node == parent->left) {
							parent->left = tempNode;
							tempNode->parent = parent;
						}
						else {
							parent->right = tempNode;
							tempNode->parent = parent;
						}

						int key = node->key;
						if (node != NULL) {
							delete node;
							node = NULL;
						}
						rebalance(parent);
						return key;
					}
				}
			}
		}

		return -1;
	}

	Node* searchMinNode(Node* node) {
		if (node == NULL) {
			return NULL;
		}
		else {
			if (node->left == NULL) {
				return node;
			}
			else {
				return searchMinNode(node->left);
			}
		}
	}

	void rebalance(Node* node) {
		if (node == NULL) {
			return;
		}

		int balance = height(node->right) - height(node->left);

		if (balance <= -2) {
			if (height(node->left->left) >= height(node->left->right)) {
				rotateRight(node);
			}
			else {
				rotateLR(node);
			}
		}
		else if (balance >= 2) {
			if (height(node->right->right) >= height(node->right->left)) {
				rotateLeft(node);
			}
			else {
				rotateRL(node);
			}
		}

		rebalance(node->parent);
	}

	Node* rotateRight(Node* node) {
		Node* parent = node->parent;
		Node* child = node->left;

		node->left = child->right;
		if (node->left != NULL)
			node->left->parent = node;

		child->right = node;
		node->parent = child;

		if (parent != NULL) {
			if (parent->left != NULL && parent->left->key == node->key) {
				parent->left = child;
			}
			else if (parent->right != NULL) {
				parent->right = child;
			}
			child->parent = parent;
		}
		else {
			child->parent = NULL;
			root = child;
		}

		return child;
	}

	Node* rotateLeft(Node* node) {
		Node* parent = node->parent;
		Node* child = node->right;

		node->right = child->left;
		if (node->right != NULL)
			node->right->parent = node;

		child->left = node;
		node->parent = child;

		if (parent != NULL) {
			if (parent->left != NULL && parent->left->key == node->key) {
				parent->left = child;
			}
			else if (parent->right != NULL) {
				parent->right = child;
			}
			child->parent = parent;
		} 
		else {
			child->parent = NULL;
			root = child;
		}

		return child;
	}

	Node* rotateLR(Node* node) {
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	Node* rotateRL(Node* node) {
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	int height(Node *node) {
		if (node == NULL) {
			return 0;
		}

		return MAX(height(node->left), height(node->right)) + 1;
	}

	void inorderTraverse(Node* node) {
		if (node) {
			inorderTraverse(node->left);
			cout << node->key << " ";
			inorderTraverse(node->right);
		}
	}

	void preorderTraverse(Node* node, int depth) {
		if (node) {
			for (int i = 0; i < depth; i++) {
				cout << "| ";
			}
			cout << node->key << endl;
			preorderTraverse(node->left, depth + 1);
			preorderTraverse(node->right, depth + 1);
		}
	}
};

AVLTree myTree;

int main() {
	srand((unsigned int) time(NULL));

	Node** root = myTree.getRoot();

	int delKey = 0;

	for (int i = 0; i < 20; i++) {
		int key = rand() % 40;

		if (i == 2) {
			delKey = key;
		}

		cout << "Add " << key << endl;
		myTree.addNode(*root, key);
	}

	cout << endl;
	myTree.preorderTraverse(*root, 0);
	cout << endl;
	cout << "Sorted : ";
	myTree.inorderTraverse(*root);
	cout << endl;

	cout << endl << "delete key : " << delKey << endl;
	myTree.deleteNode(*root, delKey);
	
	cout << endl;
	myTree.preorderTraverse(*root, 0);
	cout << endl;

	cout << "Sorted : ";
	myTree.inorderTraverse(*root);
	cout << endl;

	cout << "height : " << myTree.height(*root) << endl;

	return 0;
}
