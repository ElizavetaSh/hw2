#include "gtest/gtest.h"

extern "C" {
#include "sequence.h"
#include "input.h"
}

TEST(LIB_TEST, empty_file) 
{
    int len = defin_fsize("empty_file");
    char *file_values = charsequence_from_file(len, "empty_file");
    char result = 0;
        EXPECT_EQ(find_repeat_in_sequence(file_values, len,result), char(ER_FILE));

    free(file_values);
}


TEST(LIB_TEST, test_lib_1) 
{
    int len = defin_fsize("1.txt");
    char *file_values = charsequence_from_file(len, "1.txt");
    char result = 0;
        EXPECT_EQ(find_repeat_in_sequence(file_values, len,result), 'f');

    free(file_values);
}

TEST(LIB_TEST, test_lib_2) 
{
    int len = defin_fsize("test_file.txt");
    char *file_values = charsequence_from_file(len, "test_file.txt");
    char result = 0;
        EXPECT_EQ(find_repeat_in_sequence(file_values, len,result), 'g');

    free(file_values);
}

TEST(LIB_TEST, test_lib_3) 
{
    int len = defin_fsize("file_number_2.txt");
    char *file_values = charsequence_from_file(len, "file_number_2.txt");
    char result = 0;
        EXPECT_EQ(find_repeat_in_sequence(file_values, len,result), 'a');
        
    free(file_values);
}

int main(int argc, char **argv) {
::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}