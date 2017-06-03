#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

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
				}
				else {
					addNode(node->left, key);
				}
			}
			else {
				if (node->right == NULL) {
					node->right = new Node(key);
					node->right->parent = node;
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

	myTree.preorderTraverse(*root, 0);
	cout << endl;

	cout << "delKey : " << delKey << endl;
	myTree.deleteNode(*root, delKey);
	myTree.preorderTraverse(*root, 0);
	cout << endl;

	cout << "Sorted" << endl;
	myTree.inorderTraverse(*root);
	cout << endl;

	return 0;
}
