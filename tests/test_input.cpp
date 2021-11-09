#include "gtest/gtest.h"

extern "C" {
#include "input.h"
}

TEST(INPUT_TEST, empty_file) { 
    EXPECT_EQ(defin_fsize("empty_file.txt"),0); 
    }
    
TEST(INPUT_TEST, file_number_1) { 
    EXPECT_EQ(defin_fsize("file_number_2.txt"),14); 
    }

TEST(INPUT_TEST, file_number_2) 
{
    char arr[] = "aabbssddffjjss";
    char *file_values = charsequence_from_file(10, "file_number_2.txt");
    for (size_t i = 0; i < 10; ++i) 
        {
        EXPECT_TRUE(file_values[i]==arr[i]);
        }
    free(file_values);
}


TEST(INPUT_TEST, file_number_3) { 
    EXPECT_EQ(defin_fsize("1.txt"), 5558); 
    }


TEST(INPUT_TEST, file_number_4) 
{
    char arr_t2[] = "aaaaaaaaaaaaasssssssdd";
    char *file_values_tr = charsequence_from_file(26, "test_file.txt");
    for (size_t i = 0; i < 16; ++i) 
        {
        EXPECT_TRUE(file_values_tr[i]== arr_t2[i]);
        }
            
    free(file_values_tr);
}

int main(int argc, char **argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}