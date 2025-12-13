#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

class RoutingTable {
private:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        std::string value = "";
    };

    Node* root;

public:
    RoutingTable() {
        root = new Node();
    }

    void add(int address, int n, std::string value) {
        Node* cur = root;
        
        for (int i = 0; i < n; i++) {
            int bit = (address >> (31 - i)) & 1;
            
            if (bit == 0) {
                if (cur->left == nullptr) {
                    cur->left = new Node();
                }
                cur = cur->left;
            } else {
                if (cur->right == nullptr) {
                    cur->right = new Node();
                }
                cur = cur->right;
            }
        }
        
        cur->value = value;
    }

    std::string route(int address) {
        Node* cur = root;
        std::string best = "";
        
        for (int i = 0; i < 32; i++) {
            if (cur->value != "") {
                best = cur->value;
            }
            
            int bit = (address >> (31 - i)) & 1;
            
            if (bit == 0) {
                if (cur->left == nullptr) {
                    break;
                }
                cur = cur->left;
            } else {
                if (cur->right == nullptr) {
                    break;
                }
                cur = cur->right;
            }
        }
        
        if (best.empty()) {
            throw std::runtime_error("No matching prefix found");
        }
        
        return best;
    }
};

void run_tests() {
    RoutingTable t;

    t.add(0x80000000, 1, "eth");
    t.add(0xC0000000, 2, "ir");
    t.add(0x80000000, 2, "usb");
    t.add(0xB0000000, 4, "ppp");
    t.add(0x00000000, 3, "wifi1");
    t.add(0x20000000, 3, "wifi2");

    std::cout << "Test 1: route(0x40000000) -> Exception" << std::endl;
    try {
        t.route(0x40000000);
        std::cout << "FAIL: Expected exception" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "PASS: Caught exception" << std::endl;
    }

    std::cout << "Test 2: route(0xAF000000) -> usb" << std::endl;
    try {
        std::string res = t.route(0xAF000000);
        std::cout << "Result: " << res << std::endl;
        assert(res == "usb");
        std::cout << "PASS" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "FAIL: " << e.what() << std::endl;
    }

    std::cout << "Test 3: route(0xB0000000) -> ppp" << std::endl;
    try {
        std::string res = t.route(0xB0000000);
        assert(res == "ppp");
        std::cout << "PASS" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "FAIL: " << e.what() << std::endl;
    }

    std::cout << "Test 4: route(0xC0000000) -> ir" << std::endl;
    try {
        std::string res = t.route(0xC0000000);
        assert(res == "ir");
        std::cout << "PASS" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "FAIL: " << e.what() << std::endl;
    }
}

int main() {
    run_tests();
    return 0;
}
