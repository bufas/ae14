#pragma once

#include <cassert>
#include <vector>
#include "../PredSearchTree.h"
#include "Test.h"
#include "../PredSearchTreeFactory.h"

class BasicTest : public Test {

public:
    BasicTest(const PredSearchTreeFactory &factory) : factory(factory) {}

    void run() {
        RUN(Empty_Pred0_NoPred);
        RUN(Empty_Pred100_NoPred);
        RUN(Singleton_PredEqual_Success);
        RUN(Singleton_PredGreater_Success);
        RUN(Singleton_PredLower_NoPred);
        RUN(Singleton_PredLower_NoPred2);
        RUN(MultiUnsorted_Preds_Success);
        RUN(BigNumber_Preds_Success);
    }

private:
    PredSearchTreeFactory factory;

    void Empty_Pred0_NoPred() {
        std::vector<int> v;
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        is_equal(tree, 0, -1);
    }

    void Empty_Pred100_NoPred() {
        std::vector<int> v;
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        is_equal(tree, 100, -1);
    }

    void Singleton_PredEqual_Success() {
        int value = 5;
        std::vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        is_equal(tree, value, value);
    }

    void Singleton_PredGreater_Success() {
        int value = 5;
        std::vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        is_equal(tree, value + 5, value);
    }

    void Singleton_PredLower_NoPred() {
        int value = 5;
        std::vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        is_equal(tree, value - 5, -1);
    }

    void Singleton_PredLower_NoPred2() {
        int value = 5;
        std::vector<int> v;
        v.push_back(value);
        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        is_equal(tree, value - 2, -1);
    }

    void MultiUnsorted_Preds_Success() {
        std::vector<int> v;
        v.push_back(87);
        v.push_back(7);
        v.push_back(198);
        v.push_back(5);

        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        is_equal(tree, 10, 7);
        is_equal(tree, 198, 198);
        is_equal(tree, 501, 198);
        is_equal(tree, 4, -1);
        is_equal(tree, 5, 5);
    }

    void BigNumber_Preds_Success() {
        std::vector<int> v;
        // v.push_back(7209583);
        v.push_back(86093022);
        v.push_back(52);
        // v.push_back(1001275982);

        std::auto_ptr<PredSearchTree> tree(factory.createTree(v));
        // is_equal(tree, 7269583, 7209583);
        is_equal(tree, 209583, 52);
        // is_equal(tree, 2061275982, 1001275982);
        // is_equal(tree, 1001275982, 1001275982);
        // is_equal(tree, 1001275986, 1001275982);
        is_equal(tree, 1001275981, 86093022);
    }
};