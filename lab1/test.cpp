#include "TConst.hpp"
#include "Trit.hpp"

TEST(TritSet_Constructor, ConstructorWithCapacity){
	TSet::TritSet set(10000);
	for (uint32_t i = 0; i < 10000; i++){
		set[i] = TSet::False;
	}
	for (uint32_t i = 0; i < 10000; i++){
		EXPECT_EQ(true, set[i] == TSet::False);
	}
}

TEST(TritSet_methods, Capacity) {
    TSet::TritSet set(10);
    EXPECT_EQ(16, set.capacity());

    TSet::TritSet set1(16);
    EXPECT_EQ(16, set1.capacity());

    TSet::TritSet set2(17);
    EXPECT_EQ(32, set2.capacity());

    TSet::TritSet set3(50);
    EXPECT_EQ(64, set3.capacity());

    TSet::TritSet set4(0);
    EXPECT_EQ(0, set4.capacity());
}

TEST(TritSet_methods, ConstructorWithNucl){
    TSet::TritSet set(10000, TSet::True);
    for (size_t i = 0; i < 10000; i++){
      EXPECT_EQ(true, set[i] == TSet::True);
    }
}

TEST(TritSet_methods, getSize){
    TSet::TritSet TritSet(100);
    ASSERT_EQ(100, TritSet.getSize());
}

TEST(TritSet_methods, Trim){
    TSet::TritSet TritSet(100, TSet::True);
    TritSet.trim(22);
    ASSERT_EQ(22, TritSet.getSize());
}

TEST(TritSet_methods, Shrink){
    TSet::TritSet TritSet(100, TSet::True);
    TritSet.shrink();
    ASSERT_EQ(7, (TritSet.getSize() + TSetC::SizeUintTrits - 1)/ 16);
}

TEST(TritSet_operators, GetByIndex){
    TSet::TritSet TritSet(100, TSet::True);
    for (size_t i = 0; i < 100; i++){
        EXPECT_EQ(true, TritSet[i] == TSet::True);
    }
}

TEST(TritSet_operators, Assignment){
    TSet::TritSet TritSet1(100, TSet::True);
    TSet::TritSet TritSet2(80, TSet::False);
    TritSet2 = TritSet1;
    ASSERT_EQ((uint32_t)100, TritSet2.getSize());
    for (size_t i = 0; i < 100; i++){
        ASSERT_EQ(true, TritSet2[i] == TSet::True);
    }
}

TEST(TritSet_operators, Equate){
    TSet::TritSet TritSet(10);
    uint32_t startCapacity = TritSet.capacity();
    uint32_t startSize = TritSet.getSize();
    TritSet[2] = TSet::True;
    ASSERT_EQ(true, TritSet[2] == TSet::True);

    TritSet[3] = TSet::False;
    ASSERT_EQ(true, TritSet[3] == TSet::False);

    TritSet[4] = TSet::Unknown;
    ASSERT_EQ(true, TritSet[4] == TSet::Unknown);

    TritSet[11] = TSet::Unknown;
    ASSERT_EQ(true, TritSet[11] == TSet::Unknown);
    ASSERT_EQ(10, TritSet.getSize());
    ASSERT_EQ(16, TritSet.capacity());

    TritSet[11241] = TSet::Unknown;
    ASSERT_EQ(10, TritSet.getSize());
    ASSERT_EQ(16, TritSet.capacity());
    
    TritSet[20] = TSet::True;
    ASSERT_EQ(true, TritSet[20] == TSet::True);
    ASSERT_EQ(21, TritSet.getSize());
    ASSERT_EQ(32, TritSet.capacity());
}

TEST(TritSet_operators, IsEqual){
    TSet::TritSet arr1(17, TSet::True);
    TSet::TritSet arr2(8, TSet::False);
    TSet::TritSet arr3(10, TSet::True);
    EXPECT_EQ(false, arr1[9] == arr2[9]);
    EXPECT_EQ(true, arr1[10] == TSet::True);
    EXPECT_EQ(true, arr1[2141244] == TSet::Unknown);
    EXPECT_EQ(true, arr1[14] == arr3[9]);
}


TEST(TritSet_operators, NOT){
    TSet::TritSet set(100, TSet::True);
    TSet::TritSet set1 = !set;
    ASSERT_EQ(100, set1.getSize());
    for (size_t i = 0; i < 100; i++){
        EXPECT_EQ(true, set1[i] == TSet::False );
    }
}

TEST(TritSet_operators, TritAnd){
    TSet::TritSet arr1( 17, TSet::True);
    TSet::TritSet arr2( 8, TSet::False);
    EXPECT_EQ(true, (arr1[1] & arr2[1]) == TSet::False);
    EXPECT_EQ(true, (arr1[9] & arr2[9]) == TSet::Unknown);
    EXPECT_EQ(true, (arr1[1231] & arr2[5211]) == TSet::Unknown);
}


TEST(TritSet_operators, TritOr){
    TSet::TritSet arr1( 17, TSet::True);
    TSet::TritSet arr2( 8, TSet::False);
    EXPECT_EQ(true, (arr1[1] | arr2[1]) == TSet::True);
    EXPECT_EQ(true, (arr1[9] | arr2[9]) == TSet::True);
    EXPECT_EQ(true, (arr1[1231] | arr2[5211]) == TSet::Unknown);
    EXPECT_EQ(true, (arr1[1231] | arr2[5]) == TSet::Unknown);
}


TEST(TritSet_operators, AndTrits) {
    TSet::TritSet arr1(17, TSet::True);
    TSet::TritSet arr2(8, TSet::False);
    TSet::TritSet arr3 = arr1 & arr2;

    EXPECT_EQ(17, arr3.getSize());
    EXPECT_EQ(true, arr3[0] == TSet::False);
    EXPECT_EQ(true, arr3[9] == TSet::True);
    EXPECT_EQ(true, arr3[20] == TSet::Unknown);
    EXPECT_EQ(true, arr3[3241] == TSet::Unknown);

}

TEST(TritSet_operators, OrTrits) {
    TSet::TritSet arr1(17, TSet::True);
    TSet::TritSet arr2(8, TSet::False);
    TSet::TritSet arr3 = arr1 | arr2;

    EXPECT_EQ(17, arr3.getSize());
    EXPECT_EQ(true, arr3[0] == TSet::True);
    EXPECT_EQ(true, arr3[9] == TSet::True);
    EXPECT_EQ(true, arr3[20] == TSet::Unknown);
    EXPECT_EQ(true, arr3[3241] == TSet::Unknown);

}

TEST(TritSet_operators, NotTrits) {
    TSet::TritSet arr1(17, TSet::True);
    TSet::TritSet arr2 = !arr1;

    EXPECT_EQ(17, arr2.getSize());
    EXPECT_EQ(true, arr2[0] == TSet::False);
    EXPECT_EQ(true, arr2[16] == TSet::False);
    EXPECT_EQ(true, arr2[18] == TSet::Unknown);
    EXPECT_EQ(true, arr2[20] == TSet::Unknown);
    EXPECT_EQ(true, arr2[3241] == TSet::Unknown);
}

int main(int argc, char* argv[]) {
	 ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
