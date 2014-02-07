#pragma once

#include <cassert>
#include <vector>
#include "../PredSearchTree.h"
#include "Test.h"
#include "PredSearchTreeFactory.h"

class BasicTest : public Test {

public:
    BasicTest(const PredSearchTreeFactory &factory) : factory(factory) {}

    void run() {
        RUN(Empty_Pred0_NoPred);
        RUN(Empty_Pred0_NoPred);
        RUN(Empty_Pred100_NoPred);
        RUN(Singleton_PredEqual_Success);
        RUN(Singleton_PredGreater_Success);
        RUN(Singleton_PredLower_NoPred);
        RUN(MultiUnsorted_Preds_Success);
    }

private:
    PredSearchTreeFactory factory;

    void Empty_Pred0_NoPred() {
        std::vector<int> v;
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(0) == -1);
    }

    void Empty_Pred100_NoPred() {
        std::vector<int> v;
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(100) == -1);
    }

    void Singleton_PredEqual_Success() {
        int value = 5;
        std::vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(value) == value);
    }

    void Singleton_PredGreater_Success() {
        int value = 5;
        std::vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(value + 5) == value);
    }

    void Singleton_PredLower_NoPred() {
        int value = 5;
        std::vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        assert(tree->pred(value - 5) == -1);
    }

    void MultiUnsorted_Preds_Success() {
        std::vector<int> v;
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