#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
  TrieNode *children[8]; // 8 ptrs × 8 bytes = 64 bytes → children[0]=digit '2',
                         // children[7]=digit '9' → index = digit - '2'
  vector<string> words;  // collision list → "rocks"=76257, "socks"=76257 → same
                         // sequence, different words
  TrieNode() { fill(children, children + 8, nullptr); }
};

class T9Prediction {
private:
  TrieNode *root;

  int charToDigit(char c) {
    // YOU DERIVE: 'a'→? 'j'→? 's'→? 'z'→?
    // TRAP: arithmetic formula fails for 7(pqrs) and 9(wxyz)
    // YOUR WORK HERE
    switch (c) {
    case 'a':
    case 'b':
    case 'c':
      return 2;
    case 'd':
    case 'e':
    case 'f':
      return 3;
    case 'g':
    case 'h':
    case 'i':
      return 4;
    case 'j':
    case 'k':
    case 'l':
      return 5;
    case 'm':
    case 'n':
    case 'o':
      return 6;
    case 'p':
    case 'q':
    case 'r':
    case 's':
      return 7; // 4 letters
    case 't':
    case 'u':
    case 'v':
      return 8;
    case 'w':
    case 'x':
    case 'y':
    case 'z':
      return 9; // 4 letters
    default:
      return 0;
    }
  }

  string wordToDigits(const string &word) {
    // YOU DERIVE: "jello"→? "rocks"→? "socks"→?
    // TRAP: uppercase, non-alpha chars
    // YOUR WORK HERE
    string digits;
    for (char c : word) {
      digits += ('0' + charToDigit(c));
    }
    return digits;
  }

  void insertWord(const string &word) {
    // YOU DERIVE: traverse/create path, append word at terminal
    // YOUR WORK HERE
    string digits = wordToDigits(word);
    TrieNode *current = root;

    for (char c : digits) {
      int idx = c - '2';
      if (current->children[idx] == nullptr) {
        current->children[idx] = new TrieNode();
      }
      current = current->children[idx];
    }
    current->words.push_back(word);
  }

  void deleteNode(TrieNode *node) {
    if (node == nullptr)
      return;
    for (int i = 0; i < 8; i++) {
      deleteNode(node->children[i]);
    }
    delete node;
  }

public:
  T9Prediction() { root = new TrieNode(); }
  ~T9Prediction() { deleteNode(root); }
  void addWord(const string &word) { insertWord(word); }

  vector<string> getAllWords(const string &digits) {
    TrieNode *current = root;
    for (char c : digits) {
      int idx = c - '2';
      if (current->children[idx] == nullptr) {
        return {};
      }
      current = current->children[idx];
    }
    return current->words;
  }
};

void test_collision() {
  cout << "test_collision: ";
  T9Prediction t9;
  t9.addWord("rocks");
  t9.addWord("socks");
  vector<string> result = t9.getAllWords("76257");
  assert(result.size() == 2);
  cout << "PASS\n";
}

void test_no_match() {
  cout << "test_no_match: ";
  T9Prediction t9;
  t9.addWord("hello");
  vector<string> result = t9.getAllWords("99999");
  assert(result.empty());
  cout << "PASS\n";
}

void test_22737() {
  cout << "test_22737: ";
  T9Prediction t9;
  vector<string> words = {"acres", "bards", "barer", "bares", "barfs",
                          "baser", "bases", "caper", "capes", "cards",
                          "carer", "cares", "cases"};
  for (const auto &w : words)
    t9.addWord(w);
  vector<string> result = t9.getAllWords("22737");
  assert(result.size() == 13);
  cout << "PASS\n";
}

void test_46637() {
  cout << "test_46637: ";
  T9Prediction t9;
  vector<string> words = {"goner", "goods", "goofs", "homer", "homes",
                          "honer", "hones", "hoods", "hoofs", "inner"};
  for (const auto &w : words)
    t9.addWord(w);
  vector<string> result = t9.getAllWords("46637");
  assert(result.size() == 10);
  cout << "PASS\n";
}

void test_2273() {
  cout << "test_2273: ";
  T9Prediction t9;
  vector<string> words = {"acre", "bard", "bare", "barf", "base",
                          "cape", "card", "care", "case"};
  for (const auto &w : words)
    t9.addWord(w);
  vector<string> result = t9.getAllWords("2273");
  assert(result.size() == 9);
  cout << "PASS\n";
}

void test_729() {
  cout << "test_729: ";
  T9Prediction t9;
  vector<string> words = {"paw", "pax", "pay", "raw", "rax",
                          "ray", "saw", "sax", "say"};
  for (const auto &w : words)
    t9.addWord(w);
  vector<string> result = t9.getAllWords("729");
  assert(result.size() == 9);
  cout << "PASS\n";
}

void test_76737() {
  cout << "test_76737: ";
  T9Prediction t9;
  vector<string> words = {"popes", "pores", "poser", "poses", "roper",
                          "roses", "sords", "sorer", "sores"};
  for (const auto &w : words)
    t9.addWord(w);
  vector<string> result = t9.getAllWords("76737");
  assert(result.size() == 9);
  cout << "PASS\n";
}

void test_prefix() {
  cout << "test_prefix: ";
  T9Prediction t9;
  t9.addWord("go");
  t9.addWord("gone");
  vector<string> r1 = t9.getAllWords("46");
  vector<string> r2 = t9.getAllWords("4663");
  assert(r1.size() == 1 && r1[0] == "go");
  assert(r2.size() == 1 && r2[0] == "gone");
  cout << "PASS\n";
}

int main() {
  cout << "T9 PREDICTIVE TEXT TESTS\n";
  cout << "========================\n";
  test_collision();
  test_no_match();
  test_22737();
  test_46637();
  test_2273();
  test_729();
  test_76737();
  test_prefix();
  cout << "========================\n";
  cout << "ALL TESTS PASSED\n";
  return 0;
}
