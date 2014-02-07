#pragma once

#include <cassert>
#include <vector>
#include "../PredSearchTree.h"
#include "Test.h"
#include "PredSearchTreeFactory.h"

using namespace std;

class BasicTest : public Test {

public:
    BasicTest(const PredSearchTreeFactory &factory) : factory(factory) {}

    void run() {
        Empty_Pred0_NoPred();
        Empty_Pred100_NoPred();
        Singleton_PredEqual_Success();
        Singleton_PredGreater_Success();
        Singleton_PredLower_NoPred();
        MultiUnsorted_Preds_Success();
    }

private:
    PredSearchTreeFactory factory;

    void Empty_Pred0_NoPred() {
        vector<int> v;
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(0) == -1);
    }

    void Empty_Pred100_NoPred() {
        vector<int> v;
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(100) == -1);
    }

    void Singleton_PredEqual_Success() {
        int value = 5;
        vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(value) == value);
    }

    void Singleton_PredGreater_Success() {
        int value = 5;
        vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(value + 5) == value);
    }

    void Singleton_PredLower_NoPred() {
        int value = 5;
        vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(value - 5) == -1);
    }

    void MultiUnsorted_Preds_Success() {
        vector<int> v;
        v.push_back(87);
        v.push_back(7);
        v.push_back(198);
        v.push_back(5);

        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(10) == 7);
        assert(tree->pred(198) == 198);
        assert(tree->pred(501) == 198);
        assert(tree->pred(4) == -1);
        assert(tree->pred(5) == 5);
    }
};