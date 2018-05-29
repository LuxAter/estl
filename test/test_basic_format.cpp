#include "basic/format.hpp"
#include "gtest/gtest.h"

TEST(BasicFormatTest, Format){
  EXPECT_EQ("Hello World", estl::base::format("Hello %s", "World"));
}
