#include <vector>
#include <string>
#include <algorithm>

class Solution {
    struct Node {
        char left_char, right_char;
        int prefix_len, suffix_len, max_len;
    };

    std::vector<Node> tree;
    std::string s_ref;

    Node merge(const Node& left, const Node& right, int left_len, int right_len) {
        Node res;
        res.left_char = left.left_char;
        res.right_char = right.right_char;
        
        // Compute prefix_len
        res.prefix_len = left.prefix_len;
        if (left.prefix_len == left_len && left.right_char == right.left_char) {
            res.prefix_len += right.prefix_len;
        }
        
        // Compute suffix_len
        res.suffix_len = right.suffix_len;
        if (right.suffix_len == right_len && right.left_char == left.right_char) {
            res.suffix_len += left.suffix_len;
        }
        
        // Compute max_len
        res.max_len = std::max({left.max_len, right.max_len});
        if (left.right_char == right.left_char) {
            res.max_len = std::max(res.max_len, left.suffix_len + right.prefix_len);
        }
        
        return res;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {s_ref[start], s_ref[start], 1, 1, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

    void update(int node, int start, int end, int idx, char val) {
        if (start == end) {
            s_ref[idx] = val;
            tree[node] = {val, val, 1, 1, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

public:
    std::vector<int> longestRepeating(std::string s, std::string queryCharacters, std::vector<int>& queryIndices) {
        int n = s.length();
        s_ref = s;
        tree.resize(4 * n);
        build(1, 0, n - 1);

        std::vector<int> ans;
        int k = queryCharacters.length();
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(tree[1].max_len);
        }

        return ans;
    }
};