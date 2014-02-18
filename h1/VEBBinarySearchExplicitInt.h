#pragma once

#include <vector>
#include <algorithm>
#include <utility>
#include "BinaryExplicitIntPredSearchTree.h"

class VEBBinarySearchExplicitInt : public BinaryExplicitIntPredSearchTree {

private:
    /**
     * Return: a pair where the first is a vector containing pointers 
     * to all leaves of this subtree, and the second is a vector
     * containing indices from v which has been used in this (sub)tree.
     */
    std::pair<std::vector<IntNode*>, std::vector<int>> 
    build(const std::vector<int> &v, const int tree_size, const int idx, const int s, const int e) {
        using std::cout;
        using std::endl;
        using std::vector;

        // If tree size is 0, return
        if (tree_size == 0) {
            vector<IntNode*> res_car;
            vector<int> res_cdr;
            return std::make_pair(res_car, res_cdr);        // Return a pair of two empty vectors
        }

        // If tree size is 1, basecase, make node and return
        if (tree_size == 1) {
            int mid = (e+s+1)/2;                            // Index of the value to insert

            // cout<<"\tInserting v["<<mid<<"]="<<v[mid]<<" at pos "<<idx<<endl;

            IntNode *n = &tree[idx];
            n->value       = v[mid];
            n->child_right = -1;
            n->child_left  = -1;

            // Create the return value
            vector<IntNode*> res_car(1, n);
            vector<int> res_cdr(1, mid);
            return std::make_pair(res_car, res_cdr);        // Return a pair of vectors with size 1
        }

        //*******************************************
        //
        // If tree size > 1, recursive case
        //
        //*******************************************

        // Calculate the size of the top tree
        int h0       = (subtree_height(tree_size) + 1) / 2; // H(T)/2 rounded up
        int top_size = power_of_two(h0) - 1;                // #nodes in top tree

        // Build top tree
        // cout<<"TOP    ("<<top_size<<","<<idx<<","<<s<<","<<e<<")"<<endl;
        auto top_data   = build(v, top_size, idx, s, e);
        auto top_leaves = top_data.first;                   // Pull returned data out into separate variables
        auto top_used   = top_data.second;                  // Same as above...

        // Sort the top_data v indices (second)
        std::sort(top_used.begin(), top_used.end());

        // Calculate how big the bottom trees are going to be
        int bottom_tree_count = power_of_two(h0);           // Maximal number of bottom trees
        int bottom_min_size   = (tree_size - top_size) / bottom_tree_count; // The size of all subtrees
        int bottom_remainder  = (tree_size - top_size) % bottom_tree_count; // We need to make the first bottom_remainder contain bottom_min_size + 1 elements

        // Build bottom trees
        int bottom_s          = s;                          // Start of subarray from which to choose values to for the first bottom
        int bottom_idx        = idx + top_size;             // Index in tree for the root of the first bottom
        vector<int> bottom_used;                            // Will contain all indices from v used to build the bottom trees
        vector<IntNode*> bottom_leaves;                     // Will contain all leaves of this subtree
        for (int i = 0; i < bottom_tree_count; i++) {
            int bottom_e    = (i == bottom_tree_count-1) ? e : top_used[i] - 1; // Choose e in the last iteration as top_used[i] is out-of-bounds
            int bottom_size = bottom_min_size;
            if (i < bottom_remainder) bottom_size++;        // Add one because the tree is not complete

            // Assert that the bottom size can be filled by bottom_s to bottom_e elements
            // Tricky part
            //   
            if (bottom_size > bottom_e - bottom_s + 1) {
                bottom_remainder++;
                bottom_size--;
                // cout<<"Bottom-tree cannot be filled ("<<bottom_size<<","<<bottom_s<<","<<bottom_e<<")"<<endl;
                // exit(-1);
            }

            // Build the bottom tree
            // cout<<"BOTTOM ("<<bottom_size<<","<<bottom_idx<<","<<bottom_s<<","<<bottom_e<<")"<<endl;
            auto bot_data   = build(v, bottom_size, bottom_idx, bottom_s, bottom_e);
            auto bot_leaves = bot_data.first;               // Pull returned data out into separate variables (same as for top tree)
            auto idxes_used = bot_data.second;              // Same as above...

            // Link the bottom tree with the top tree
            IntNode *top_node_to_update = top_leaves[i/2];  // This is the node we need to update
            if (i % 2 == 0) top_node_to_update->child_left = bottom_idx;        // Link as left child
            else top_node_to_update->child_right = bottom_idx;                  // Link as right child

            // Merge bot_data for this tree with other bottom trees
            bottom_leaves.insert(bottom_leaves.end(), bot_leaves.begin(), bot_leaves.end());
            bottom_used.insert(bottom_used.end(), idxes_used.begin(), idxes_used.end());

            // Update bottom_s and bottom_idx
            bottom_s = bottom_e + 2;                        // Skip the element that is already used in the top tree
            bottom_idx += bottom_size;                      // Previous indices are used in previous bottom tree
        }

        // Merge top and bottom indices used and return the result
        bottom_used.insert(bottom_used.begin(), top_used.begin(), top_used.end());
        return std::make_pair(bottom_leaves, bottom_used);
    }
    
    // std::vector<int> build(const std::vector<int> &v, const int tree_size, const int idx, const int s, const int e) {
    //     using std::cout;
    //     using std::endl;

    //     // Create the result vector
    //     std::vector<int> res;

    //     // If tree size is 0, return
    //     if (tree_size == 0) return res;

    //     // If tree size is 1, basecase, make node and return
    //     if (tree_size == 1) {
    //         int mid = (e+s+1)/2;                            // Index of the value to insert

    //         cout<<"\tInserting v["<<mid<<"]="<<v[mid]<<" at pos "<<idx<<endl;

    //         IntNode *n = &tree[idx];
    //         n->value       = v[mid];
    //         n->child_right = -1;
    //         n->child_left  = -1;

    //         res.push_back(mid);
    //         return res;
    //     }

    //     //*******************************************
    //     //
    //     // If tree size > 1, recursive case
    //     //
    //     //*******************************************

    //     // Calculate the size of the top tree
    //     int h0       = (subtree_height(tree_size) + 1) / 2; // H(T)/2 rounded up
    //     int top_size = power_of_two(h0) - 1;                // #nodes in top tree

    //     // Build top tree
    //     cout<<"TOP    ("<<top_size<<","<<idx<<","<<s<<","<<e<<")"<<endl;
    //     auto top_used = build(v, top_size, idx, s, e);

    //     // Sort the top_used
    //     std::sort(top_used.begin(), top_used.end());

    //     // Calculate how big the bottom trees are going to be
    //     int bottom_tree_count = power_of_two(h0);           // Maximal number of bottom trees
    //     int bottom_min_size   = (tree_size - top_size) / bottom_tree_count; // The size of all subtrees
    //     int bottom_remainder  = (tree_size - top_size) % bottom_tree_count; // We need to make the first bottom_remainder contain bottom_min_size + 1 elements

    //     // Build bottom trees
    //     int bottom_s          = s;                          // Start of subarray from which to choose values to for the first bottom
    //     int bottom_idx        = idx + top_size;             // Index in tree for the root of the first bottom
    //     std::vector<int> bottom_used;                       // Will contain all indices from v used to build the bottom trees
    //     for (int i = 0; i < bottom_tree_count; i++) {
    //         int bottom_e    = (i == bottom_tree_count-1) ? e : top_used[i] - 1; // Choose e in the last iteration as top_used[i] is out-of-bounds
    //         int bottom_size = bottom_min_size;
    //         if (i < bottom_remainder) bottom_size++;        // Add one because the tree is not complete

    //         // Assert that the bottom size can be filled by bottom_s to bottom_e elements
    //         if (bottom_size > bottom_e - bottom_s + 1) {
    //             cout<<"Bottom-tree cannot be filled ("<<bottom_size<<","<<bottom_s<<","<<bottom_e<<")"<<endl;
    //             exit(-1);
    //         }

    //         // Build the bottom tree
    //         cout<<"BOTTOM ("<<bottom_size<<","<<bottom_idx<<","<<bottom_s<<","<<bottom_e<<")"<<endl;
    //         auto idxes_used = build(v, bottom_size, bottom_idx, bottom_s, bottom_e);

    //         // TODO link the bottom tree with the top tree

    //         // Merge idxes_used with bottom_used
    //         bottom_used.insert(bottom_used.end(), idxes_used.begin(), idxes_used.end());

    //         // Update bottom_s and bottom_idx
    //         bottom_s = bottom_e + 2;                        // Skip the element that is already used in the top tree
    //         bottom_idx += bottom_size;                      // Previous indices are used in previous bottom tree
    //     }

    //     // Merge top and bottom indices used and return the result
    //     res.insert(res.end(), top_used.begin(), top_used.end());
    //     res.insert(res.end(), bottom_used.begin(), bottom_used.end());
    //     return res;
    // }
    
    // std::vector<int> build(const std::vector<int> &v, int root_idx, int idx, int s, int e, int skew) {
    //     using std::cout;
    //     using std::endl;

    //     std::vector<int> res;

    //     if (s > e) return res;

    //     cout << idx << ", " << s << ", " << e << endl;

    //     // This is just a single node tree (recursion base case)
    //     if (e == s) {
    //         cout << "BASECASE" << endl;
    //         IntNode *n = &tree[idx];
    //         n->value       = v[s];
    //         n->child_right = -1;
    //         n->child_left  = -1;

    //         res.push_back(idx);
    //         return res;
    //     }

    //     // We have more than one node (the recursive case)
    //     int h0       = (subtree_height(e - s + 1, skew) + 1) / 2;
    //     int top_size = power_of_two(h0) - 1;

    //     // Build top tree
    //     cout << "TOP:    ";
    //     auto top_leaves          = build(v, root_idx, idx, s, e, skew);
    //     int top_tree_child_spots = top_leaves.size() * 2;
    //     int bottom_tree_count    = std::max(top_tree_child_spots, e - s - top_size + 1);
    //     cout << "bottom_tree_count = " << bottom_tree_count << endl;

    //     // Build bottom trees
    //     int bottom_s   = s + top_size;
    //     int bottom_idx = idx + top_size;
    //     cout << "making " << bottom_tree_count << " bottom trees" << endl;
    //     for (int i = 0; i < bottom_tree_count; i++) {
    //         // Calculate size of bottom tree and end index
    //         int this_tree_size = (e - bottom_s + 1) / (bottom_tree_count - i);
    //         cout << "this_tree_size = " << this_tree_size << endl;
    //         int bottom_e = bottom_s + this_tree_size - 1;

    //         // Build bottom tree and insert leaves into the result
    //         cout << "BOTTOM: ";
    //         auto bottom_leaves = build(v, bottom_idx, bottom_s, bottom_e, skew);
    //         res.insert(res.end(), bottom_leaves.begin(), bottom_leaves.end());

    //         // Connect this bottom tree to the top tree (even index is left child)
    //         if (i % 2 == 0) (&tree[top_leaves[i/2]])->child_left = bottom_idx;
    //         else (&tree[top_leaves[i/2]])->child_right = bottom_idx;

    //         // Increment indexes for next bottom tree
    //         bottom_s += this_tree_size;
    //         bottom_idx += this_tree_size;
    //     }

    //     return res;
    // }

    int subtree_height(int size) {
        int height = 0;
        while (size > 0) size -= power_of_two(height++);
        return height;
    }

    int power_of_two(int exponent) {
        return 1 << exponent;
    }

    void print() const {
        std::cout << "[ ";
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            std::cout << (*it).value << " ";
        }
        std::cout << "]" << std::endl;
    }


protected:
    int get_root_idx() const { return 0; }
    
public:
    VEBBinarySearchExplicitInt(const std::vector<int> &v, int skew = 50) : BinaryExplicitIntPredSearchTree(v) {
        std::vector<int> temp(v);
        std::sort(temp.begin(), temp.end());
        // std::cout<<"TYPE   (size="<<temp.size()<<", idx=0, s=0, e="<<(temp.size() - 1)<<")"<<std::endl;
        build(temp, temp.size(), 0, 0, temp.size() - 1);
        // print();
        // make_dot("vEBExInt.dot");
    }
};