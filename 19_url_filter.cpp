// 19_url_filter.cpp
// URL Filter: blacklist lookup via unordered_set
// N=10^6 blacklist entries × L=50 avg URL length = 5×10^7 bytes = 50 MB heap
// for blacklist M=10^6 input URLs × O(1) lookup = 10^6 hash computations →
// hash("example.com") ≈ 50 ns → 10^6 × 50 ns = 50 ms total
// unordered_set<string> memory: bucket_count × 8 bytes (ptrs) + N ×
// (sizeof(node) + L) = N × (24 + 50) = 74N bytes ≈ 74 MB for N=10^6

#include <cassert> // assert(expr) → if !expr → __assert_fail() → abort() → exit code 134
#include <chrono> // high_resolution_clock::now() → returns time_point → duration = end - start → duration_cast<milliseconds>(d).count() → int64_t ms
#include <filesystem> // std::filesystem::remove(path) → unlink() syscall → returns true if deleted, false if not found
#include <fstream> // std::ifstream, std::ofstream → file descriptor int fd → fd=3 for first opened file after stdin(0),stdout(1),stderr(2)
#include <iostream> // std::cout, std::cerr → stdout 0x7fff0000, stderr 0x7fff0008
#include <sstream> // std::stringstream → internal buffer → str() returns copy → buffer at 0x3000, capacity grows 2x
#include <string> // std::string → SSO: len≤15 → inline 16 bytes, len>15 → heap ptr 8 bytes + size 8 bytes + capacity 8 bytes = 24 bytes stack + heap
#include <unordered_set> // bucket_count=8 initially → load_factor=N/bucket_count → rehash when load_factor>1.0 → bucket_count doubles → 8→16→32→64→...
#include <vector> // push_back: size=4, capacity=4 → push 5th → realloc capacity=8 → copy 4 elements → O(N) amortized O(1)

// Middle calculation: filter(input, output) with N=1000 URLs, B=500 blacklisted
// Line 10 of filter(): if (blacklist.count(url)) → hash(url) → bucket[hash %
// bucket_count] → traverse chain url="blocked.com" → hash("blocked.com") =
// 0x7A3B2C1D → bucket_count=1024 → 0x7A3B2C1D % 1024 = 541 →
// bucket[541]→"blocked.com"→∅ → found → count=1 url="allowed.com" →
// hash("allowed.com") = 0x1F2E3D4C → 0x1F2E3D4C % 1024 = 332 → bucket[332]→∅ →
// not found → count=0

// Large scale: B=10^7 blacklist entries → memory = 10^7 × 74 bytes = 740 MB →
// fits in RAM M=10^7 input URLs → 10^7 × O(1) = 10^7 ops → 10^7 × 50 ns = 500
// ms → acceptable Small scale: B=1, M=1 → 1 lookup → instant Fractional: M=7,
// wrap n=10 → 10/7 = 1 remainder 3 → urls[0,1,2] checked 2x, urls[3,4,5,6]
// checked 1x? No → i%7: 0,1,2,3,4,5,6,0,1,2 → urls[0,1,2] get 2 checks

class URLFilter {
private:
  std::unordered_set<std::string> blacklist;
  // Memory layout at 0x1000:
  // ┌──────────────────────────────────────────────────────────────────────────────────────────┐
  // │ 0x1000: bucket_count = 8 (size_t, 8 bytes) │ │ 0x1008: buckets_ptr →
  // 0x2000 [8 pointers × 8 bytes = 64 bytes]                           │ │
  // 0x1010: size = 3 (size_t, 8 bytes) → 3 URLs in blacklist │ │ 0x1018:
  // max_load_factor = 1.0 (float, 4 bytes) │
  // └──────────────────────────────────────────────────────────────────────────────────────────┘
  // Buckets at 0x2000:
  // ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────┐
  // │ bucket[0] @ 0x2000 → ∅ │ │ bucket[1] @ 0x2008 → 0x3000 (node: "bad1.com")
  // → ∅                                                      │ │ bucket[2] @
  // 0x2010 → ∅ │ │ bucket[3] @ 0x2018 → 0x3100 (node: "bad2.com") → 0x3200
  // (node: "bad3.com") → ∅  ← collision chain len=2 │ │ bucket[4] @ 0x2020 → ∅
  // │ │ bucket[5] @ 0x2028 → ∅ │ │ bucket[6] @ 0x2030 → ∅ │ │ bucket[7] @
  // 0x2038 → ∅ │
  // └─────────────────────────────────────────────────────────────────────────────────────────────────────────┘
  // Node at 0x3000: { hash_cache=0x1A2B, next=∅, value="bad1.com" } → 8+8+24 =
  // 40 bytes per node

public:
  // ════════════════════════════════════════════════════════════════════════════════════════════
  // clearFilter()
  // Before: size=3, bucket[1]→node, bucket[3]→node→node
  // After:  size=0, all buckets→∅
  // Time: O(N) → must deallocate N nodes → N=10^6 → 10^6 × free() → ~100 ms
  // ════════════════════════════════════════════════════════════════════════════════════════════
  void clearFilter() {
    // USER IMPLEMENTS: 1 line
    blacklist.clear();
  }

  // ════════════════════════════════════════════════════════════════════════════════════════════
  // addBlacklist(filename)
  // File at path="/data/blacklist.txt" → fd=open(path, O_RDONLY) → fd=3
  // File content: "bad1.com\nbad2.com\nbad3.com\n" → 30 bytes → 3 lines
  // getline reads into buffer: line.data()=0x4000, line.size()=8 for "bad1.com"
  // insert: hash("bad1.com")=0x1A2B → 0x1A2B % 8 = 3 → bucket[3]→new_node
  // ════════════════════════════════════════════════════════════════════════════════════════════
  void addBlacklist(const std::string &filename) {
    // USER IMPLEMENTS: ~10 lines
    // open file
    // while getline
    // trim \r if present
    // skip empty
    // insert into blacklist
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
      if (!line.empty() && line.back() == '\r')
        line.pop_back();
      if (!line.empty())
        blacklist.insert(line);
    }
  }

  // ════════════════════════════════════════════════════════════════════════════════════════════
  // filter(input_file, output_file)
  // input has 5 URLs: ["good1","bad1","good2","bad2","good3"]
  // blacklist has 2: {"bad1","bad2"}
  // iter₁: url="good1" → hash("good1")=0xAAAA → bucket[2]→∅ → count=0 → skip
  // iter₂: url="bad1"  → hash("bad1")=0xBBBB  → bucket[3]→"bad1" → count=1 →
  // write output: ["bad1","bad2"] → 2 lines written
  // ════════════════════════════════════════════════════════════════════════════════════════════
  void filter(const std::string &input_file, const std::string &output_file) {
    // USER IMPLEMENTS: ~10 lines
    // open input ifstream
    // open output ofstream
    // while getline
    // trim \r
    // if in blacklist → write to output
    std::ifstream in(input_file);
    std::ofstream out(output_file);
    std::string url;
    while (std::getline(in, url)) {
      if (!url.empty() && url.back() == '\r')
        url.pop_back();
      if (!url.empty() && blacklist.count(url))
        out << url << '\n';
    }
  }

  // ════════════════════════════════════════════════════════════════════════════════════════════
  // perf(input_file, n)
  // input has 3 URLs: ["u0","u1","u2"] → urls.size()=3
  // n=7 → indices: 0%3=0, 1%3=1, 2%3=2, 3%3=0, 4%3=1, 5%3=2, 6%3=0 → sequence:
  // u0,u1,u2,u0,u1,u2,u0 blacklist={"u1"} → blocked at i=1,4 → passed at
  // i=0,2,3,5,6 → passed=5 timing: start=t₀, end=t₁, duration=t₁-t₀ → n=10^6,
  // ~50ms expected
  // ════════════════════════════════════════════════════════════════════════════════════════════
  void perf(const std::string &input_file, int n) {
    // USER IMPLEMENTS: ~15 lines
    // read all URLs into vector
    // check urls.empty() → avoid division by zero
    // start timer
    // loop i=0 to n-1
    //   idx = i % urls.size()
    //   if not in blacklist → passed++
    // stop timer
    // print passed, time_ms
    std::ifstream in(input_file);
    std::string url;
    std::vector<std::string> urls;
    while (std::getline(in, url)) {
      if (!url.empty() && url.back() == '\r')
        url.pop_back();
      if (!url.empty())
        urls.push_back(url);
    }
    if (urls.empty())
      return;
    int passed = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
      int idx = i % urls.size();
      if (!blacklist.count(urls[idx]))
        passed++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << passed << " " << duration.count() << std::endl;
  }

  // test helpers
  size_t size() const { return blacklist.size(); } // size=3 → return 3
  bool contains(
      const std::string &url) const { // url="bad1.com" → count=1 → return true
    return blacklist.count(url) > 0;  // url="good.com" → count=0 → return false
  }
};

// ════════════════════════════════════════════════════════════════════════════════════════════════
// Test utilities
// ════════════════════════════════════════════════════════════════════════════════════════════════

std::string createTempFile(const std::string &content) {
  // counter=0 → filename="/tmp/url_filter_test_0.txt"
  // counter=1 → filename="/tmp/url_filter_test_1.txt"
  // ofstream opens with O_WRONLY|O_CREAT|O_TRUNC → fd=3 → write content → close
  static int counter = 0;
  std::string filename =
      "/tmp/url_filter_test_" + std::to_string(counter++) + ".txt";
  std::ofstream out(filename);
  out << content;
  out.close();
  return filename;
}

std::string readFile(const std::string &filename) {
  // ifstream opens → fd=3 → rdbuf() returns filebuf* → stringstream copies all
  // bytes file has 20 bytes → buffer copies 20 bytes → str() returns 20-char
  // string
  std::ifstream in(filename);
  std::stringstream buffer;
  buffer << in.rdbuf();
  return buffer.str();
}

void cleanup(const std::string &filename) {
  // unlink("/tmp/url_filter_test_0.txt") → removes inode → frees disk blocks
  std::filesystem::remove(filename);
}

// ════════════════════════════════════════════════════════════════════════════════════════════════
// Test cases
// ════════════════════════════════════════════════════════════════════════════════════════════════

void test_clearFilter() {
  std::cout << "test_clearFilter... ";
  URLFilter filter;
  std::string bl = createTempFile(
      "bad1.com\nbad2.com\nbad3.com\n"); // 3 lines → 3 entries expected
  filter.addBlacklist(bl);
  assert(filter.size() == 3); // before clear: size=3
  filter.clearFilter();
  assert(filter.size() == 0);           // after clear: size=0
  assert(!filter.contains("bad1.com")); // lookup returns false
  cleanup(bl);
  std::cout << "PASSED\n";
}

void test_addBlacklist_basic() {
  std::cout << "test_addBlacklist_basic... ";
  URLFilter filter;
  std::string bl = createTempFile("bad1.com\nbad2.com\nbad3.com\n");
  filter.addBlacklist(bl);
  assert(filter.size() == 3);          // 3 unique URLs
  assert(filter.contains("bad1.com")); // hash→bucket→found
  assert(filter.contains("bad2.com"));
  assert(filter.contains("bad3.com"));
  assert(!filter.contains("good1.com")); // not in set
  cleanup(bl);
  std::cout << "PASSED\n";
}

void test_addBlacklist_duplicates() {
  std::cout << "test_addBlacklist_duplicates... ";
  URLFilter filter;
  std::string bl =
      createTempFile("bad1.com\nbad2.com\nbad1.com\n"); // bad1 appears 2x
  filter.addBlacklist(bl);
  assert(filter.size() == 2); // unordered_set deduplicates → only 2 unique
  cleanup(bl);
  std::cout << "PASSED\n";
}

void test_addBlacklist_empty_lines() {
  std::cout << "test_addBlacklist_empty_lines... ";
  URLFilter filter;
  std::string bl = createTempFile("bad1.com\n\nbad2.com\n\n"); // 2 empty lines
  filter.addBlacklist(bl);
  assert(filter.size() == 2); // empty lines skipped
  cleanup(bl);
  std::cout << "PASSED\n";
}

void test_addBlacklist_windows_crlf() {
  std::cout << "test_addBlacklist_windows_crlf... ";
  URLFilter filter;
  std::string bl =
      createTempFile("bad1.com\r\nbad2.com\r\n"); // CRLF = 0x0D 0x0A
  filter.addBlacklist(bl);
  assert(filter.size() == 2);
  assert(filter.contains("bad1.com")); // must match "bad1.com" not "bad1.com\r"
  cleanup(bl);
  std::cout << "PASSED\n";
}

void test_addBlacklist_multiple_files() {
  std::cout << "test_addBlacklist_multiple_files... ";
  URLFilter filter;
  std::string bl1 = createTempFile("bad1.com\nbad2.com\n");
  std::string bl2 = createTempFile("bad3.com\nbad4.com\n");
  filter.addBlacklist(bl1);
  filter.addBlacklist(bl2);
  assert(filter.size() == 4); // accumulates: 2 + 2 = 4
  cleanup(bl1);
  cleanup(bl2);
  std::cout << "PASSED\n";
}

void test_filter_basic() {
  std::cout << "test_filter_basic... ";
  URLFilter filter;
  std::string bl = createTempFile("bad1.com\nbad2.com\n");
  filter.addBlacklist(bl);
  std::string input = createTempFile(
      "good1.com\nbad1.com\ngood2.com\nbad2.com\ngood3.com\n"); // 5 URLs, 2 bad
  std::string output = "/tmp/url_filter_out_basic.txt";
  filter.filter(input, output);
  std::string result = readFile(output);
  assert(result == "bad1.com\nbad2.com\n"); // only bad URLs in output
  cleanup(bl);
  cleanup(input);
  cleanup(output);
  std::cout << "PASSED\n";
}

void test_filter_empty_blacklist() {
  std::cout << "test_filter_empty_blacklist... ";
  URLFilter filter; // no blacklist added
  std::string input = createTempFile("url1.com\nurl2.com\n");
  std::string output = "/tmp/url_filter_out_empty.txt";
  filter.filter(input, output);
  std::string result = readFile(output);
  assert(result == ""); // nothing filtered
  cleanup(input);
  cleanup(output);
  std::cout << "PASSED\n";
}

void test_filter_all_blacklisted() {
  std::cout << "test_filter_all_blacklisted... ";
  URLFilter filter;
  std::string bl = createTempFile("url1.com\nurl2.com\nurl3.com\n");
  filter.addBlacklist(bl);
  std::string input =
      createTempFile("url1.com\nurl2.com\nurl3.com\n"); // all in blacklist
  std::string output = "/tmp/url_filter_out_all.txt";
  filter.filter(input, output);
  std::string result = readFile(output);
  assert(result == "url1.com\nurl2.com\nurl3.com\n"); // all filtered
  cleanup(bl);
  cleanup(input);
  cleanup(output);
  std::cout << "PASSED\n";
}

void test_filter_empty_input() {
  std::cout << "test_filter_empty_input... ";
  URLFilter filter;
  std::string bl = createTempFile("bad.com\n");
  filter.addBlacklist(bl);
  std::string input = createTempFile(""); // empty input
  std::string output = "/tmp/url_filter_out_empty_in.txt";
  filter.filter(input, output);
  std::string result = readFile(output);
  assert(result == ""); // no output
  cleanup(bl);
  cleanup(input);
  cleanup(output);
  std::cout << "PASSED\n";
}

void test_perf_basic() {
  std::cout << "test_perf_basic... ";
  URLFilter filter;
  std::string bl = createTempFile("bad1.com\n");
  filter.addBlacklist(bl);
  std::string input =
      createTempFile("good1.com\nbad1.com\ngood2.com\n"); // 3 URLs, 1 bad
  std::cout << "\n  n=3, expected passed=2: ";
  filter.perf(input, 3); // good1→pass, bad1→block, good2→pass → passed=2
  cleanup(bl);
  cleanup(input);
  std::cout << "  PASSED\n";
}

void test_perf_wrap() {
  std::cout << "test_perf_wrap... ";
  URLFilter filter;
  std::string bl = createTempFile("url1.com\n");
  filter.addBlacklist(bl);
  std::string input =
      createTempFile("url0.com\nurl1.com\nurl2.com\n"); // 3 URLs
  std::cout << "\n  n=7, 3 URLs, url1 blocked: ";
  // i=0→url0→pass, i=1→url1→block, i=2→url2→pass, i=3→url0→pass,
  // i=4→url1→block, i=5→url2→pass, i=6→url0→pass passed=5, blocked=2
  filter.perf(input, 7);
  cleanup(bl);
  cleanup(input);
  std::cout << "  PASSED\n";
}

void test_perf_empty_input() {
  std::cout << "test_perf_empty_input... ";
  URLFilter filter;
  std::string input = createTempFile(""); // empty
  std::cout << "\n  n=10, empty input (should handle gracefully): ";
  filter.perf(input,
              10); // must not crash: urls.size()=0 → i%0 undefined → must check
  cleanup(input);
  std::cout << "  PASSED\n";
}

void test_perf_n_zero() {
  std::cout << "test_perf_n_zero... ";
  URLFilter filter;
  std::string input = createTempFile("url.com\n");
  std::cout << "\n  n=0: ";
  filter.perf(input, 0); // loop runs 0 times → passed=0, time≈0ms
  cleanup(input);
  std::cout << "  PASSED\n";
}

void test_clearFilter_then_add() {
  std::cout << "test_clearFilter_then_add... ";
  URLFilter filter;
  std::string bl1 = createTempFile("old1.com\nold2.com\n");
  filter.addBlacklist(bl1);
  assert(filter.size() == 2);
  filter.clearFilter();
  assert(filter.size() == 0);
  std::string bl2 = createTempFile("new1.com\n");
  filter.addBlacklist(bl2);
  assert(filter.size() == 1);
  assert(!filter.contains("old1.com")); // cleared
  assert(filter.contains("new1.com"));  // newly added
  cleanup(bl1);
  cleanup(bl2);
  std::cout << "PASSED\n";
}

// ════════════════════════════════════════════════════════════════════════════════════════════════
// main
// ════════════════════════════════════════════════════════════════════════════════════════════════

int main() {
  std::cout << "=== URL Filter Tests ===\n\n";
  test_clearFilter();
  test_addBlacklist_basic();
  test_addBlacklist_duplicates();
  test_addBlacklist_empty_lines();
  test_addBlacklist_windows_crlf();
  test_addBlacklist_multiple_files();
  test_filter_basic();
  test_filter_empty_blacklist();
  test_filter_all_blacklisted();
  test_filter_empty_input();
  test_perf_basic();
  test_perf_wrap();
  test_perf_empty_input();
  test_perf_n_zero();
  test_clearFilter_then_add();
  std::cout << "\n=== All tests passed! ===\n";
  return 0;
}
