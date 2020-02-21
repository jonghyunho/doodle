#include <iostream>
#include <string>

using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode {
  struct TrieNode* children[ALPHABET_SIZE];
  bool end_of_word;

  TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) children[i] = nullptr;
    end_of_word = false;
  }
};

TrieNode* getNode() { return new TrieNode(); }

void insert(TrieNode* root, string key) {
  if (root == nullptr) return;

  TrieNode* node = root;

  for (uint32_t i = 0; i < key.size(); i++) {
    int index = key[i] - 'a';
    if (!node->children[index]) node->children[index] = getNode();

    node = node->children[index];
  }

  node->end_of_word = true;
}

bool search(TrieNode* root, string key) {
  if (root == nullptr) return false;

  TrieNode* node = root;

  for (uint32_t i = 0; i < key.size(); i++) {
    int index = key[i] - 'a';
    if (!node->children[index]) return false;

    node = node->children[index];
  }

  return node && node->end_of_word;
}

int main() {
  // Input keys (use only 'a' through 'z'
  // and lower case)
  string keys[] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
  int n = sizeof(keys) / sizeof(keys[0]);

  struct TrieNode* root = getNode();

  // Construct trie
  for (int i = 0; i < n; i++) insert(root, keys[i]);

  // Search for different keys
  search(root, "the") ? cout << "Yes\n" : cout << "No\n";
  search(root, "these") ? cout << "Yes\n" : cout << "No\n";
  search(root, "their") ? cout << "Yes\n" : cout << "No\n";
  search(root, "thaw") ? cout << "Yes\n" : cout << "No\n";
  return 0;
}
