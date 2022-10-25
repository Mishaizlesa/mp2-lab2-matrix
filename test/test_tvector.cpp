#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(10);
    
    ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(a);
    EXPECT_EQ(a, b);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(a);
    b[0]=1;
    EXPECT_NE(a, b);
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);
    EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int>a(5);
    EXPECT_ANY_THROW(a[-1]=0);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int>a(5);
    EXPECT_ANY_THROW(a[10]=0);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int>a(5);
    EXPECT_NO_THROW(a=a);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(5);
    EXPECT_NO_THROW(a=b);
}
TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(4);
    EXPECT_NO_THROW(a=b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(4);
    a=b;
    EXPECT_EQ(4, a.size());
}
TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(a);
    EXPECT_EQ(true, a==b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int>a(5);
    EXPECT_EQ(true, a==a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(10);
    EXPECT_NE(true, a==b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    int v=4;
    TDynamicVector<int>a(5);
    TDynamicVector<int>res(5);
    res[0]=4;res[1]=4;res[2]=4;res[3]=4;res[4]=4;
    TDynamicVector<int>tmp=a+v;
    EXPECT_EQ(tmp, res);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    int v=-4;
    TDynamicVector<int>a(5);
    TDynamicVector<int>res(5);
    res[0]=4;res[1]=4;res[2]=4;res[3]=4;res[4]=4;
    TDynamicVector<int>tmp=a-v;
    EXPECT_EQ(tmp, res);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    int v=-4;
    TDynamicVector<int>a(5);
    for(int i=0;i<4;++i) a[i]=1;
    TDynamicVector<int>res(5);
    for(int i=0;i<4;++i) res[i]=-4;
    TDynamicVector<int>tmp=a*v;
    EXPECT_EQ(tmp, res);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(5);
    a[1]=1;b[1]=2;
    TDynamicVector<int>tmp=a+b;
    TDynamicVector<int>res(5);
    res[1]=3;
    EXPECT_EQ(res, tmp);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(6);
    EXPECT_ANY_THROW(a+b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(5);
    a[1]=1;b[1]=2;
    TDynamicVector<int>tmp=a-b;
    TDynamicVector<int>res(5);
    res[1]=-1;
    EXPECT_EQ(res, tmp);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(6);
    EXPECT_ANY_THROW(a-b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(5);
    a[1]=1;b[1]=2;
    int tmp=a*b;
    int res=2;
    EXPECT_EQ(res, tmp);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int>a(5);
    TDynamicVector<int>b(6);
    EXPECT_ANY_THROW(a*b);
}

