#include <ctime>
#include <iostream>
#include <random>

#define N 20

struct Node {
  int value;
  struct Node* next = nullptr;

  Node(int _value) : value(_value) {}
};

Node* insertNode(Node* node, int value) {
  if (node == nullptr) {
    return nullptr;
  }
  node->next = new Node(value);
  return node->next;
}

void printList(Node* node) {
  if (node == nullptr) return;
  
  printList(node->next);
  std::cout << node->value << " ";
}

std::pair<Node*, Node*> reverseList(Node* node) {
  if (node == nullptr) return std::make_pair(nullptr, nullptr);
  if (node->next == nullptr) return std::make_pair(node, node);

  std::pair<Node*, Node*> nextList = reverseList(node->next);
  Node* lastNode = nextList.second;
  if (lastNode) {
    lastNode->next = node;
    node->next = nullptr;
  }

  return std::make_pair(nextList.first, node);
}

int main() {
  std::srand(uint8_t(std::time(nullptr)));

  Node* root = new Node(std::rand() % 100);
  Node* node = root;
  for (int i = 1; i < N; i++) {
    int value = std::rand() % 100;
    node = insertNode(node, value);
  }

  printList(root);
  std::cout << std::endl << std::endl;

  std::pair<Node*, Node*> linked_list = reverseList(root);

  root = linked_list.first;
  printList(root);
  std::cout << std::endl << std::endl;
}

/*
 * Reult:
 * 45 17 43 21 46 26 65 18 76 1 47 46 81 83 19 70 75 89 22 64
 *
 * 64 22 89 75 70 19 83 81 46 47 1 76 18 65 26 46 21 43 17 45
 */
