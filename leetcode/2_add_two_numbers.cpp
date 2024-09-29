#include <cstdlib>
#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *current1 = l1;
    ListNode *current2 = l2;
    while (1) {

      printf("\niteration\n");
      addNodes(current1, current2);
      if (current1->next != NULL && current2->next != NULL) {
        printf("next not null\n");
        current1 = current1->next;
        current2 = current2->next;
      } else {
        printf("next null\n");
        break;
      }
    }
    printf("while loop end\n");

    printf("\ncleanup\n");
    if (current1->next == NULL && current2->next != NULL) {
      current1->next = current2->next;
    }
    return l1;
  }
  void addNodes(ListNode *node1, ListNode *node2) {
    int sum = node1->val + node2->val;
    printf("%d + %d = %d\n", node1->val, node2->val, sum);
    int pos1 = sum % 10;
    node1->val = pos1;
    printf("node1: %d\n", node1->val);

    ListNode *pos2 = new ListNode(sum / 10);
    if (pos2->val == 0) {
      return;
    }

    if (node1->next != NULL) {
      printf("pos2: %d\n", pos2->val);
      return addNodes(node1->next, pos2);
    } else {
      printf("ok\n");
      node1->next = pos2;
    }
  }
};

int main() {
  Solution sol;
  ListNode el1 = ListNode(3);
  ListNode el2 = ListNode(4, &el1);
  ListNode l1 = ListNode(2, &el2); // [2,4,3]
  ListNode l2el1 = ListNode(4);
  ListNode l2el2 = ListNode(6, &l2el1);
  ListNode l2 = ListNode(5, &l2el2); // [5,6,4]

  // ListNode l1 = ListNode(9);
  // ListNode l2 = ListNode(
  //     1, new ListNode(9, new ListNode(9, new ListNode(8, new ListNode(9)))));

  // ListNode l1 = ListNode(0);
  // ListNode l2 = ListNode(7, new ListNode(3));
  ListNode *result = sol.addTwoNumbers(&l1, &l2);
  printf("result: ");
  while (result != NULL) {
    printf("%d,", result->val);
    result = result->next;
  }
  printf("\n");
  return 0;
}
