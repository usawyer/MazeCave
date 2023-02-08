#include <gtest/gtest.h>

#include "./Maze/cave.h"
#include "./Maze/maze.h"

TEST(cave_tests, setter_test) {
  Cave test;
  test.Setter(3, 4, 2, 6, 0.0);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 4);
  EXPECT_EQ(test.GetBirth(), 2);
  EXPECT_EQ(test.GetDeath(), 6);
}

TEST(cave_tests, create_test) {
  Cave test;
  test.Setter(3, 3, 2, 6, 0.0);

  Matrix compare(3, 3);

  EXPECT_EQ(test.GetMatrix().EqMatrix(compare), true);
}

TEST(cave_tests, next_step_test) {
  Cave test;
  test.Setter(3, 3, 0, 6, 0.0);
  test.NextStep(test.GetBirth(), test.GetDeath());

  Matrix compare(3, 3);
  compare(0, 0) = 1;
  compare(0, 1) = 1;
  compare(0, 2) = 1;
  compare(1, 0) = 1;
  compare(1, 1) = 0;
  compare(1, 2) = 1;
  compare(2, 0) = 1;
  compare(2, 1) = 1;
  compare(2, 2) = 1;

  EXPECT_EQ(test.GetMatrix().EqMatrix(compare), true);
}

TEST(cave_tests, parser_test) {
  Cave test;
  test.Parser("./examples/cave/cave_3X3.txt");

  Matrix compare(3, 3);
  compare(0, 0) = 1;
  compare(0, 1) = 0;
  compare(0, 2) = 1;
  compare(1, 0) = 0;
  compare(1, 1) = 0;
  compare(1, 2) = 1;
  compare(2, 0) = 0;
  compare(2, 1) = 0;
  compare(2, 2) = 1;

  EXPECT_EQ(test.GetMatrix().EqMatrix(compare), true);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(maze_tests, generate) {
  Maze test;
  test.Generate(3, 3);
  EXPECT_EQ(test.GetCols(), 3);
  EXPECT_EQ(test.GetRows(), 3);
}

TEST(maze_tests, open_file) {
  Maze test;
  std::string path = "./examples/maze/maze_4X4.txt";
  test.ReadFromFile(path);
  Matrix result_h_m(4, 4);
  result_h_m(0, 0) = 1;
  result_h_m(0, 1) = 0;
  result_h_m(0, 2) = 1;
  result_h_m(0, 3) = 0;
  result_h_m(1, 0) = 0;
  result_h_m(1, 1) = 0;
  result_h_m(1, 2) = 1;
  result_h_m(1, 3) = 0;
  result_h_m(2, 0) = 1;
  result_h_m(2, 1) = 1;
  result_h_m(2, 2) = 0;
  result_h_m(2, 3) = 1;
  result_h_m(3, 0) = 1;
  result_h_m(3, 1) = 1;
  result_h_m(3, 2) = 1;
  result_h_m(3, 3) = 1;
  Matrix result_v_m(4, 4);
  result_v_m(0, 0) = 0;
  result_v_m(0, 1) = 0;
  result_v_m(0, 2) = 0;
  result_v_m(0, 3) = 1;
  result_v_m(1, 0) = 1;
  result_v_m(1, 1) = 0;
  result_v_m(1, 2) = 1;
  result_v_m(1, 3) = 1;
  result_v_m(2, 0) = 0;
  result_v_m(2, 1) = 1;
  result_v_m(2, 2) = 0;
  result_v_m(2, 3) = 1;
  result_v_m(3, 0) = 0;
  result_v_m(3, 1) = 0;
  result_v_m(3, 2) = 0;
  result_v_m(3, 3) = 1;
  EXPECT_EQ(test.GetHorizontallWall().EqMatrix(result_h_m), 1);
  EXPECT_EQ(test.GetVerticalWall().EqMatrix(result_v_m), 1);
  EXPECT_EQ(test.GetCols(), 4);
  EXPECT_EQ(test.GetRows(), 4);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
