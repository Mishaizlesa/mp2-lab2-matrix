#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);
    
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}
TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int>a(5);
    a[1][1]=10;
    a[2][2]=33;
    TDynamicMatrix<int>b(a);
    EXPECT_EQ(a, b);
    //ADD_FAILURE();
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int>a(5);
    a[1][1]=10;
    a[2][2]=33;
    TDynamicMatrix<int>b(a);
    b[1][1]=-1;
    EXPECT_NE(a, b);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int>a(5);
    int x=a.size();
    EXPECT_EQ(a, 5);
}
TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int>a(5);
    a[1][1]=22;
    a[1][1]=a[1][1]-3;
    EXPECT_EQ(a[1][1], 19);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int>a(5);
    EXPECT_ANY_THROW(a[-3][1]=1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int>a(5);
    EXPECT_ANY_THROW(a[6][1]=1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int>a(5);
    EXPECT_NO_THROW(a=a);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(5);
    EXPECT_NO_THROW(a=b);
}
TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(4);
    EXPECT_NO_THROW(a=b);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(4);
    a=b;
    EXPECT_EQ(a.size(), 4);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(a);
    EXPECT_EQ(a==b, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int>a(5);
    EXPECT_EQ(a==a, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(6);
    EXPECT_EQ(a==b, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(5);
    a[1][1]=1;
    b[1][1]=2;
    TDynamicMatrix<int>c=a+b;
    TDynamicMatrix<int>res(5);
    res[1][1]=3;
    EXPECT_EQ(c, res);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(6);
    EXPECT_ANY_THROW(a+b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(5);
    a[1][1]=1;
    b[1][1]=2;
    TDynamicMatrix<int>c=a-b;
    TDynamicMatrix<int>res(5);
    res[1][1]=-1;
    EXPECT_EQ(c, res);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int>a(5);
    TDynamicMatrix<int>b(6);
    EXPECT_ANY_THROW(a-b);
}
