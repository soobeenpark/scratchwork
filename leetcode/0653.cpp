#include <bits/stdc++.h>
using namespace std;

/* Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
  public:
    // DFS
    bool findTargetHelper(TreeNode *root, int k, set<int> &s) {
        if (root == nullptr) {
            return false;
        }

        int num = root->val;
        int matching = k - num;
        if (s.find(matching) != s.end()) {
            return true;
        }

        s.insert(num);
        return findTargetHelper(root->left, k, s) ||
               findTargetHelper(root->right, k, s);
    }

    bool findTarget(TreeNode *root, int k) {
        set<int> s;
        return findTargetHelper(root, k, s);
    }
};

class SolutionAlt1 {
  public:
    // BFS
    bool findTarget(TreeNode *root, int k) {
        queue<TreeNode *> q;
        set<int> s;
        q.push(root);

        while (!q.empty()) {
            TreeNode *curr = q.front();
            q.pop();
            if (curr == nullptr) {
                continue;
            }
            int num = curr->val;
            int matching = k - num;
            if (s.find(matching) != s.end()) {
                return true;
            }
            s.insert(num);

            q.push(curr->left);
            q.push(curr->right);
        }
        return false;
    }
};

class SolutionAlt2 {
  public:
    void addNumsToArray(TreeNode *root, vector<int> &nums) {
        if (root == NULL) {
            return;
        }

        // In-order traversal
        addNumsToArray(root->left, nums);
        nums.push_back(root->val);
        addNumsToArray(root->right, nums);
    }

    // First do in order traversal of the BST to get sorted array.
    // Then, use the two pointers method on this sorted array to get answer.
    bool findTarget(TreeNode *root, int k) {
        // In-order traversal to get array
        vector<int> nums;
        addNumsToArray(root, nums);

        // Two pointers method
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            if (nums[left] + nums[right] == k) {
                return true;
            } else if (nums[left] + nums[right] < k) {
                left++;
            } else {
                right--;
            }
        }
        return false;
    }
};
