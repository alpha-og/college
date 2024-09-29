#include <iostream>
#include <unordered_map>
#include <vector>
class Solution {
public:
  std::vector<int> twoSum(std::vector<int> &nums, int target) {
    std::unordered_map<int, int> map;

    for (int i = 0; i < nums.size() - 1; i++) {
      int diff = target - nums[i];
      if (map.find(diff) != map.end()) {
        return {i, map[diff]};
      } else {
        map.insert({nums[i], i});
      }
    }
    return {};
  }
};

int main() {
  Solution sol;
  std::vector<int> input = {2, 7, 11, 15};
  std::vector<int> output = sol.twoSum(input, 9);
  std::cout << "\n[";
  for (int index : output) {
    std::cout << index << ",";
  }
  std::cout << "]\n";
}
