#include <gtest/gtest.h>
#include "../src/s21_list.h"

TEST(ListTest, DefaultConstructor) {
    s21::list<int> l;
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0U);
}

TEST(ListTest, SizeConstructor) {
    s21::list<int> l(5);
    EXPECT_EQ(l.size(), 5U);
    EXPECT_FALSE(l.empty());
}

TEST(ListTest, InitializerList) {
    s21::list<int> l{1, 2, 3, 4};
    EXPECT_EQ(l.size(), 4U);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 4);
}

TEST(ListTest, CopyConstructor) {
    s21::list<int> a{10, 20, 30};
    s21::list<int> b(a);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.front(), b.front());
    EXPECT_EQ(a.back(), b.back());
}

TEST(ListTest, MoveConstructor) {
    s21::list<int> a{1, 2, 3};
    s21::list<int> b(std::move(a));
    EXPECT_EQ(b.size(), 3U);
    EXPECT_TRUE(a.empty());
}

TEST(ListTest, PopBackDoesNotDecreaseSize) {
    s21::list<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    l.pop_back();

    EXPECT_EQ(l.size(), 2);
}

TEST(ListTest, PushFrontPopFront) {
    s21::list<int> l;
    l.push_front(10);
    l.push_front(20);
    EXPECT_EQ(l.front(), 20);
    l.pop_front();
    EXPECT_EQ(l.front(), 10);
}

TEST(ListTest, InsertAtEnd) {
    s21::list<int> l{1, 2};
    auto it = l.end();
    l.insert(it, 999);
    EXPECT_EQ(l.back(), 999);
    EXPECT_EQ(l.size(), 3U);
}

TEST(ListTest, ReverseEvenSize) {
    s21::list<int> l{1, 2, 3, 4};
    l.reverse();
    EXPECT_EQ(l.front(), 4);
    EXPECT_EQ(l.back(), 1);
}

TEST(ListTest, ClearAndSize) {
    s21::list<int> l{1, 2, 3};
    l.clear();
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0U);
}