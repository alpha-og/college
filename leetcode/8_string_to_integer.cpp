#include <cstdint>
#include <iostream>
#include <string>

class Solution {
public:
  int myAtoi(std::string s) {
    int is_token = 0;
    int64_t result = 0;
    int sign = 1;

    for (int i = 0; i < s.length(); i++) {
      if (is_token == 0) {
        if (s[i] == ' ') {
          continue;
        } else if (s[i] == '+') {
          sign = 1;
          is_token = 1;
        } else if (s[i] == '-') {
          sign = -1;
          is_token = 1;
        } else if (s[i] >= '0' && s[i] <= '9') {
          result = result * 10 + (int)s[i] - (int)'0';
          is_token = 1;
        } else {
          break;
        }
      } else {
        if (result == 0 && s[i] == '0') {
          continue;
        }
        if (s[i] >= '0' && s[i] <= '9') {
          if (sign == 1) {
            int64_t tmp = result * 10 + ((int)s[i] - (int)'0');
            // std::cout << tmp << "\n";
            if (tmp > INT32_MAX) {
              std::cout << "Overflow\n";
              result = INT32_MAX;
            } else {
              result = tmp;
            }
          } else {
            int64_t tmp = result * 10 - ((int)s[i] - (int)'0');
            // std::cout << tmp << "\n";
            if (tmp < INT32_MIN) {
              std::cout << "Overflow\n";
              result = INT32_MIN;
            } else {
              result = tmp;
            }
          }
        } else {
          is_token = 0;
          break;
        }
      }
    }
    return result;
  }
};

int main() {
  Solution sol;
  std::string input = "  -042";
  int output = sol.myAtoi(input);
  std::cout << "Result: " << output << "\n";
}
