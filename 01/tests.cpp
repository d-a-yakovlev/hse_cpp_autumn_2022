#include <iostream>
#include <gtest/gtest.h>

#include "allocator.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestAllocator, test_makeAllocator)
{
    Allocator testedAllocator;
    testedAllocator.makeAllocator( 10 );
    {
        char *res = testedAllocator.alloc( 10 );
        ASSERT_TRUE( res != nullptr );
    }

    {
        char *res = testedAllocator.alloc( 1 );
        ASSERT_EQ( res, nullptr );
    }

    testedAllocator.makeAllocator( 0 );
    {
        char *res = testedAllocator.alloc( 1 );
        ASSERT_EQ( res, nullptr );
    }
}

TEST(TestAllocator, test_alloc)
{
    Allocator testedAllocator;
    testedAllocator.makeAllocator( 10 );
    {
        char *res = testedAllocator.alloc( 4 );
        ASSERT_TRUE( res != nullptr );
    }

    {
        char *res = testedAllocator.alloc( 6 );
        ASSERT_TRUE( res != nullptr );
    }

    {
        char *res = testedAllocator.alloc( 10 );
        ASSERT_EQ( res, nullptr );
    }
}

TEST(TestAllocator, test_reset)
{
    Allocator testedAllocator;
    testedAllocator.makeAllocator( 10 );
    {
        char *res = testedAllocator.alloc( 10 );
        ASSERT_TRUE( res != nullptr );
    }

    testedAllocator.reset();
    {
        char *res = testedAllocator.alloc( 10 );
        ASSERT_TRUE( res != nullptr );
    }
}

TEST(TestAllocator, test_seq_call_makeAllocator)
{
    Allocator testedAllocator;
    testedAllocator.makeAllocator( 1 );

    char* chp = testedAllocator.alloc(1);
    *chp = 'A';

    testedAllocator.makeAllocator( 1 );

    char* chpNew = testedAllocator.alloc(1);

    if (chp == chpNew)
    { 
        ASSERT_TRUE(*chp != 'A');
        ASSERT_TRUE(*chpNew == 0);
    }
    else
    { 
        ASSERT_TRUE(*chpNew == 0);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}