#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cassert>

// hash_table: dict_words → O(1) lookup
// file_words → check each → O(file_size)
// total: O(dict_size + file_size)

std::vector<std::string> find_misspelled_hash(
    const std::vector<std::string>& file_words,
    const std::vector<std::string>& dict_words) {
    // dict_words=[cat,dog,bird] → hash_table_size=3
    // insert: hash(cat)=h₁, hash(dog)=h₂, hash(bird)=h₃
    // lookup file_word: hash(word) → O(1)
    
    std::vector<std::string> incorrect;
    
    // dict_words=[hello,world,test,spelling] → unordered_set size=4
    // insert: hash(hello), hash(world), hash(test), hash(spelling)
    std::unordered_set<std::string> dict(dict_words.begin(), dict_words.end());
    
    // file_words=[hello,wrld,test,speling]
    // check hello → dict.find(hello)≠end() ✓ → skip
    // check wrld → dict.find(wrld)==end() ✗ → incorrect.push_back(wrld)
    // check test → dict.find(test)≠end() ✓ → skip
    // check speling → dict.find(speling)==end() ✗ → incorrect.push_back(speling)
    for (const auto& word : file_words) {
        if (dict.find(word) == dict.end()) {
            incorrect.push_back(word);
        }
    }
    
    return incorrect;
}

// sorted_array: dict_words → sort → O(dict_size×log(dict_size))
// file_words → binary_search each → O(file_size×log(dict_size))
// total: O(dict_size×log(dict_size) + file_size×log(dict_size))

std::vector<std::string> find_misspelled_sorted(
    const std::vector<std::string>& file_words,
    std::vector<std::string> dict_words) {
    // dict_words=[cat,dog,bird] → sort → [bird,cat,dog]
    // binary_search: low=0, high=2, mid=1
    // compare file_word with dict_words[mid]
    
    std::vector<std::string> incorrect;
    
    // TODO: sort dict_words
    // TODO: for each word in file_words
    //       binary_search in sorted dict_words
    //       if not found → add to incorrect
    std::sort(dict_words.begin(), dict_words.end());
    for (const auto& word : file_words)
    {
        if ( !std::binary_search(dict_words.begin(), dict_words.end(), word))
        {
            incorrect.push_back(word);
        }
    }
    
    return incorrect;
}

// Test case: file_words=5, dict_words=1000
// hash: build=1000, lookup=5×1 → total=1005
// sorted: sort=1000×10, lookup=5×10 → total=10050
// hash=10× faster

void test_basic() {
    // file_words=[hello,wrld,test,speling]
    // dict_words=[hello,world,test,spelling]
    // incorrect=[wrld,speling]
    std::vector<std::string> file_words = {"hello", "wrld", "test", "speling"};
    std::vector<std::string> dict_words = {"hello", "world", "test", "spelling"};
    
    auto result_hash = find_misspelled_hash(file_words, dict_words);
    // expected: size=2, words=[wrld,speling]
    assert(result_hash.size() == 2);
    assert(std::find(result_hash.begin(), result_hash.end(), "wrld") != result_hash.end());
    assert(std::find(result_hash.begin(), result_hash.end(), "speling") != result_hash.end());
    
    auto result_sorted = find_misspelled_sorted(file_words, dict_words);
    assert(result_sorted.size() == 2);
    assert(std::find(result_sorted.begin(), result_sorted.end(), "wrld") != result_sorted.end());
    assert(std::find(result_sorted.begin(), result_sorted.end(), "speling") != result_sorted.end());
}

void test_all_correct() {
    // file_words=[cat,dog]
    // dict_words=[cat,dog,bird]
    // incorrect=[]
    std::vector<std::string> file_words = {"cat", "dog"};
    std::vector<std::string> dict_words = {"cat", "dog", "bird"};
    
    auto result_hash = find_misspelled_hash(file_words, dict_words);
    // expected: size=0
    assert(result_hash.size() == 0);
    
    auto result_sorted = find_misspelled_sorted(file_words, dict_words);
    assert(result_sorted.size() == 0);
}

void test_all_incorrect() {
    // file_words=[xyz,abc]
    // dict_words=[cat,dog]
    // incorrect=[xyz,abc]
    std::vector<std::string> file_words = {"xyz", "abc"};
    std::vector<std::string> dict_words = {"cat", "dog"};
    
    auto result_hash = find_misspelled_hash(file_words, dict_words);
    // expected: size=2
    assert(result_hash.size() == 2);
    
    auto result_sorted = find_misspelled_sorted(file_words, dict_words);
    assert(result_sorted.size() == 2);
}

void test_empty_file() {
    // file_words=[]
    // dict_words=[cat,dog]
    // incorrect=[]
    std::vector<std::string> file_words = {};
    std::vector<std::string> dict_words = {"cat", "dog"};
    
    auto result_hash = find_misspelled_hash(file_words, dict_words);
    // expected: size=0
    assert(result_hash.size() == 0);
    
    auto result_sorted = find_misspelled_sorted(file_words, dict_words);
    assert(result_sorted.size() == 0);
}

void test_empty_dict() {
    // file_words=[cat,dog]
    // dict_words=[]
    // incorrect=[cat,dog]
    std::vector<std::string> file_words = {"cat", "dog"};
    std::vector<std::string> dict_words = {};
    
    auto result_hash = find_misspelled_hash(file_words, dict_words);
    // expected: size=2, all_words_incorrect
    assert(result_hash.size() == 2);
    
    auto result_sorted = find_misspelled_sorted(file_words, dict_words);
    assert(result_sorted.size() == 2);
}

void test_duplicates() {
    // file_words=[cat,cat,dog]
    // dict_words=[cat,dog]
    // incorrect=[] (duplicates handled)
    std::vector<std::string> file_words = {"cat", "cat", "dog"};
    std::vector<std::string> dict_words = {"cat", "dog"};
    
    auto result_hash = find_misspelled_hash(file_words, dict_words);
    // expected: size=0 or size=0 (both cat instances correct)
    assert(result_hash.size() == 0);
    
    auto result_sorted = find_misspelled_sorted(file_words, dict_words);
    assert(result_sorted.size() == 0);
}

void test_single_word() {
    // file_words=[cat]
    // dict_words=[cat]
    // incorrect=[]
    std::vector<std::string> file_words = {"cat"};
    std::vector<std::string> dict_words = {"cat"};
    
    auto result_hash = find_misspelled_hash(file_words, dict_words);
    // expected: size=0
    assert(result_hash.size() == 0);
    
    auto result_sorted = find_misspelled_sorted(file_words, dict_words);
    assert(result_sorted.size() == 0);
}

void test_large_input() {
    // file_words=1000, dict_words=10000
    // hash: build=10000, lookup=1000×1=1000 → total=11000
    // sorted: sort=10000×13, lookup=1000×13=13000 → total=143000
    std::vector<std::string> file_words;
    std::vector<std::string> dict_words;
    
    // dict: word_0, word_1, ..., word_9999
    for (int i = 0; i < 10000; i++) {
        dict_words.push_back("word_" + std::to_string(i));
    }
    
    // file: word_0, word_2, word_4, ..., word_1998 (even indices)
    for (int i = 0; i < 1000; i++) {
        file_words.push_back("word_" + std::to_string(i * 2));
    }
    
    auto result_hash = find_misspelled_hash(file_words, dict_words);
    // expected: size=0 (all even indices exist in dict)
    assert(result_hash.size() == 0);
    
    auto result_sorted = find_misspelled_sorted(file_words, dict_words);
    assert(result_sorted.size() == 0);
}

int main() {
    test_basic();
    test_all_correct();
    test_all_incorrect();
    test_empty_file();
    test_empty_dict();
    test_duplicates();
    test_single_word();
    test_large_input();
    
    std::cout << "All tests passed" << std::endl;
    return 0;
}
