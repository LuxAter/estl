// Copyright 2018 Arden Rasmussen

#include "gtest/gtest.h"
#include "variable.hpp"

TEST(VariableTest, Bool) {
  estl::variable::Variable var(false);
  EXPECT_EQ(false, var.GetBool());
  EXPECT_EQ(estl::variable::Variable::BOOL, var.Type());
  bool test = var;
  EXPECT_EQ(false, test);
}
TEST(VariableTest, Char) {
  char a = 'a';
  signed char b = 'b';
  unsigned char c = 'c';
  estl::variable::Variable vara(a);
  EXPECT_EQ('a', vara.GetChar());
  EXPECT_EQ(estl::variable::Variable::CHAR, vara.Type());
  char testa = vara;
  EXPECT_EQ('a', testa);
  estl::variable::Variable varb(b);
  EXPECT_EQ('b', varb.GetSignedChar());
  EXPECT_EQ(estl::variable::Variable::SIGNED_CHAR, varb.Type());
  signed char testb = varb;
  EXPECT_EQ('b', testb);
  estl::variable::Variable varc(c);
  EXPECT_EQ('c', varc.GetUnsignedChar());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_CHAR, varc.Type());
  unsigned char testc = varc;
  EXPECT_EQ('c', testc);
}
TEST(VariableTest, Integer) {
  signed short int a = 1;
  unsigned short int b = 2;
  signed int c = 3;
  unsigned int d = 4;
  signed long int e = 5;
  unsigned long int f = 6;
  signed long long int g = 7;
  unsigned long long int h = 8;
  estl::variable::Variable vara(a);
  EXPECT_EQ(1, vara.GetSignedShortInt());
  EXPECT_EQ(estl::variable::Variable::SIGNED_SHORT_INT, vara.Type());
  signed short int testa = vara;
  EXPECT_EQ(1, testa);
  estl::variable::Variable varb(b);
  EXPECT_EQ(2, varb.GetUnsignedShortInt());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_SHORT_INT, varb.Type());
  unsigned short int testb = varb;
  EXPECT_EQ(2, testb);
  estl::variable::Variable varc(c);
  EXPECT_EQ(3, varc.GetSignedInt());
  EXPECT_EQ(estl::variable::Variable::SIGNED_INT, varc.Type());
  signed int testc = varc;
  EXPECT_EQ(3, testc);
  estl::variable::Variable vard(d);
  EXPECT_EQ(4, vard.GetUnsignedInt());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_INT, vard.Type());
  unsigned int testd = vard;
  EXPECT_EQ(4, testd);
  estl::variable::Variable vare(e);
  EXPECT_EQ(5, vare.GetSignedLongInt());
  EXPECT_EQ(estl::variable::Variable::SIGNED_LONG_INT, vare.Type());
  signed long int teste = vare;
  EXPECT_EQ(5, teste);
  estl::variable::Variable varf(f);
  EXPECT_EQ(6, varf.GetUnsignedLongInt());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_LONG_INT, varf.Type());
  unsigned long int testf = varf;
  EXPECT_EQ(6, testf);
  estl::variable::Variable varg(g);
  EXPECT_EQ(7, varg.GetSignedLongLongInt());
  EXPECT_EQ(estl::variable::Variable::SIGNED_LONG_LONG_INT, varg.Type());
  signed long long int testg = varg;
  EXPECT_EQ(7, testg);
  estl::variable::Variable varh(h);
  EXPECT_EQ(8, varh.GetUnsignedLongLongInt());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_LONG_LONG_INT, varh.Type());
  unsigned long long int testh = varh;
  EXPECT_EQ(8, testh);
}
TEST(VariableTest, Float) {
  float a = 3.1415;
  double b = 2.7182;
  long double c = 1.4142;
  estl::variable::Variable vara(a);
  EXPECT_EQ(float(3.1415), vara.GetFloat());
  EXPECT_EQ(estl::variable::Variable::FLOAT, vara.Type());
  float testa = vara;
  EXPECT_EQ(float(3.1415), testa);
  estl::variable::Variable varb(b);
  EXPECT_EQ(2.7182, varb.GetDouble());
  EXPECT_EQ(estl::variable::Variable::DOUBLE, varb.Type());
  double testb = varb;
  EXPECT_EQ(2.7182, testb);
  estl::variable::Variable varc(c);
  EXPECT_EQ(1.4142, varc.GetLongDouble());
  EXPECT_EQ(estl::variable::Variable::LONG_DOUBLE, varc.Type());
  long double testc = varc;
  EXPECT_EQ(1.4142, testc);
}
TEST(VariableTest, String) {
  std::string a = "Hello World!";
  const char* b = "Good Bye World!";
  estl::variable::Variable vara(a);
  EXPECT_EQ("Hello World!", vara.GetString());
  EXPECT_EQ(estl::variable::Variable::STRING, vara.Type());
  std::string testa = vara;
  EXPECT_EQ("Hello World!", testa);
  estl::variable::Variable varb(b);
  EXPECT_EQ("Good Bye World!", varb.GetCharArray());
  EXPECT_EQ(estl::variable::Variable::CHAR_ARRAY, varb.Type());
  const char* testb = varb;
  EXPECT_EQ("Good Bye World!", testb);
}

TEST(VariableTest, BoolVector) {
  estl::variable::Variable var({false, true});
  var.PushBack(true);
  EXPECT_EQ(std::vector<bool>({false, true, true}), var.GetBoolVector());
  EXPECT_EQ(estl::variable::Variable::BOOL_VECTOR, var.Type());
  std::vector<bool> test = var;
  EXPECT_EQ(std::vector<bool>({false, true, true}), test);
}

TEST(VariableTest, CharVector) {
  char a = 'a', b = 'b';
  signed char c = 'c', d = 'd';
  unsigned char e = 'e', f = 'f';
  estl::variable::Variable vara({a, b});
  vara.PushBack(b);
  EXPECT_EQ(std::vector<char>({'a', 'b', 'b'}), vara.GetCharVector());
  EXPECT_EQ(estl::variable::Variable::CHAR_VECTOR, vara.Type());
  std::vector<char> testa = vara;
  EXPECT_EQ(std::vector<char>({'a', 'b', 'b'}), testa);
  estl::variable::Variable varb({c, d});
  varb.PushBack(d);
  EXPECT_EQ(std::vector<signed char>({'c', 'd', 'd'}),
            varb.GetSignedCharVector());
  EXPECT_EQ(estl::variable::Variable::SIGNED_CHAR_VECTOR, varb.Type());
  std::vector<signed char> testb = varb;
  EXPECT_EQ(std::vector<signed char>({'c', 'd', 'd'}), testb);
  estl::variable::Variable varc({e, f});
  varc.PushBack(f);
  EXPECT_EQ(std::vector<unsigned char>({'e', 'f', 'f'}),
            varc.GetUnsignedCharVector());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_CHAR_VECTOR, varc.Type());
  std::vector<unsigned char> testc = varc;
  EXPECT_EQ(std::vector<unsigned char>({'e', 'f', 'f'}), testc);
}

TEST(VariableTest, IntegerVector) {
  signed short int aa = 1, ab = 2;
  unsigned short int ba = 3, bb = 4;
  signed int ca = 5, cb = 6;
  unsigned int da = 7, db = 8;
  signed long int ea = 9, eb = 10;
  unsigned long int fa = 11, fb = 12;
  signed long long int ga = 13, gb = 14;
  unsigned long long int ha = 15, hb = 16;
  estl::variable::Variable vara({aa, ab});
  vara.PushBack(ab);
  EXPECT_EQ(std::vector<signed short int>({1, 2, 2}),
            vara.GetSignedShortIntVector());
  EXPECT_EQ(estl::variable::Variable::SIGNED_SHORT_INT_VECTOR, vara.Type());
  std::vector<signed short int> testa = vara;
  EXPECT_EQ(std::vector<signed short int>({1, 2, 2}), testa);
  estl::variable::Variable varb({ba, bb});
  varb.PushBack(bb);
  EXPECT_EQ(std::vector<unsigned short int>({3, 4, 4}),
            varb.GetUnsignedShortIntVector());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_SHORT_INT_VECTOR, varb.Type());
  std::vector<unsigned short int> testb = varb;
  EXPECT_EQ(std::vector<unsigned short int>({3, 4, 4}), testb);
  estl::variable::Variable varc({ca, cb});
  varc.PushBack(cb);
  EXPECT_EQ(std::vector<signed int>({5, 6, 6}), varc.GetSignedIntVector());
  EXPECT_EQ(estl::variable::Variable::SIGNED_INT_VECTOR, varc.Type());
  std::vector<signed int> testc = varc;
  EXPECT_EQ(std::vector<signed int>({5, 6, 6}), testc);
  estl::variable::Variable vard({da, db});
  vard.PushBack(db);
  EXPECT_EQ(std::vector<unsigned int>({7, 8, 8}), vard.GetUnsignedIntVector());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_INT_VECTOR, vard.Type());
  std::vector<unsigned int> testd = vard;
  EXPECT_EQ(std::vector<unsigned int>({7, 8, 8}), testd);
  estl::variable::Variable vare({ea, eb});
  vare.PushBack(eb);
  EXPECT_EQ(std::vector<signed long int>({9, 10, 10}),
            vare.GetSignedLongIntVector());
  EXPECT_EQ(estl::variable::Variable::SIGNED_LONG_INT_VECTOR, vare.Type());
  std::vector<signed long int> teste = vare;
  EXPECT_EQ(std::vector<signed long int>({9, 10, 10}), teste);
  estl::variable::Variable varf({fa, fb});
  varf.PushBack(fb);
  EXPECT_EQ(std::vector<unsigned long int>({11, 12, 12}),
            varf.GetUnsignedLongIntVector());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_LONG_INT_VECTOR, varf.Type());
  std::vector<unsigned long int> testf = varf;
  EXPECT_EQ(std::vector<unsigned long int>({11, 12, 12}), testf);
  estl::variable::Variable varg({ga, gb});
  varg.PushBack(gb);
  EXPECT_EQ(std::vector<signed long long int>({13, 14, 14}),
            varg.GetSignedLongLongIntVector());
  EXPECT_EQ(estl::variable::Variable::SIGNED_LONG_LONG_INT_VECTOR, varg.Type());
  std::vector<signed long long int> testg = varg;
  EXPECT_EQ(std::vector<signed long long int>({13, 14, 14}), testg);
  estl::variable::Variable varh({ha, hb});
  varh.PushBack(hb);
  EXPECT_EQ(std::vector<unsigned long long int>({15, 16, 16}),
            varh.GetUnsignedLongLongIntVector());
  EXPECT_EQ(estl::variable::Variable::UNSIGNED_LONG_LONG_INT_VECTOR,
            varh.Type());
  std::vector<unsigned long long int> testh = varh;
  EXPECT_EQ(std::vector<unsigned long long int>({15, 16, 16}), testh);
}

TEST(VariableTest, FloatVector) {
  float a = 1.1, b = 1.2;
  double c = 2.1, d = 2.2;
  long double e = 3.1, f = 3.2;
  estl::variable::Variable vara({a, b});
  vara.PushBack(b);
  EXPECT_EQ(std::vector<float>({1.1, 1.2, 1.2}), vara.GetFloatVector());
  EXPECT_EQ(estl::variable::Variable::FLOAT_VECTOR, vara.Type());
  std::vector<float> testa = vara;
  EXPECT_EQ(std::vector<float>({1.1, 1.2, 1.2}), testa);
  estl::variable::Variable varb({c, d});
  varb.PushBack(d);
  EXPECT_EQ(std::vector<double>({2.1, 2.2, 2.2}), varb.GetDoubleVector());
  EXPECT_EQ(estl::variable::Variable::DOUBLE_VECTOR, varb.Type());
  std::vector<double> testb = varb;
  EXPECT_EQ(std::vector<double>({2.1, 2.2, 2.2}), testb);
  estl::variable::Variable varc({e, f});
  varc.PushBack(f);
  EXPECT_EQ(std::vector<long double>({3.1, 3.2, 3.2}),
            varc.GetLongDoubleVector());
  EXPECT_EQ(estl::variable::Variable::LONG_DOUBLE_VECTOR, varc.Type());
  std::vector<long double> testc = varc;
  EXPECT_EQ(std::vector<long double>({3.1, 3.2, 3.2}), testc);
}

TEST(VariableTest, StringVector) {
  std::string a = "Hello", b = "Bye";
  const char *c = "World", *d = "Day";
  estl::variable::Variable vara({a, b});
  vara.PushBack(b);
  EXPECT_EQ(std::vector<std::string>({"Hello", "Bye", "Bye"}),
            vara.GetStringVector());
  EXPECT_EQ(estl::variable::Variable::STRING_VECTOR, vara.Type());
  std::vector<std::string> testa = vara;
  EXPECT_EQ(std::vector<std::string>({"Hello", "Bye", "Bye"}), testa);
  estl::variable::Variable varb({c, d});
  varb.PushBack(d);
  EXPECT_EQ(std::vector<const char*>({"World", "Day", "Day"}),
            varb.GetCharArrayVector());
  EXPECT_EQ(estl::variable::Variable::CHAR_ARRAY_VECTOR, varb.Type());
  std::vector<const char*> testb = varb;
  EXPECT_EQ(std::vector<const char*>({"World", "Day", "Day"}), testb);
}

TEST(VariableTest, BooleanOperators) {
  estl::variable::Variable a(15), b(3.1415), c(std::string("Hello World!"));
  EXPECT_EQ(a == a, true);
  EXPECT_EQ(a != a, false);
  EXPECT_EQ(a != b, true);
  EXPECT_EQ(a < b, true);
  EXPECT_EQ(a > c, false);
  EXPECT_EQ(a <= c, true);
  EXPECT_EQ(a >= b, false);
}

TEST(VariableTest, StreamOperator) {
  bool a = true;
  char b = 'a';
  signed char c = 'b';
  unsigned char d = 'c';
  signed short int e = 1;
  unsigned short int f = 2;
  signed int g = 3;
  unsigned int h = 4;
  signed long int i = 5;
  unsigned long int j = 6;
  signed long long int k = 7;
  unsigned long long int l = 8;
  float m = 1.5;
  double n = 3.1415;
  long double o = 2.7182;
  std::string p = "Hello World!";
  const char* q = "Goodbye World!";
  std::stringstream out;
  estl::variable::Variable var;
  var = a;
  out << var;
  EXPECT_EQ("1", out.str());
  out.str(std::string());
  var = b;
  out << var;
  EXPECT_EQ("a", out.str());
  out.str(std::string());
  var = c;
  out << var;
  EXPECT_EQ("b", out.str());
  out.str(std::string());
  var = d;
  out << var;
  EXPECT_EQ("c", out.str());
  out.str(std::string());
  var = e;
  out << var;
  EXPECT_EQ("1", out.str());
  out.str(std::string());
  var = f;
  out << var;
  EXPECT_EQ("2", out.str());
  out.str(std::string());
  var = g;
  out << var;
  EXPECT_EQ("3", out.str());
  out.str(std::string());
  var = h;
  out << var;
  EXPECT_EQ("4", out.str());
  out.str(std::string());
  var = i;
  out << var;
  EXPECT_EQ("5", out.str());
  out.str(std::string());
  var = j;
  out << var;
  EXPECT_EQ("6", out.str());
  out.str(std::string());
  var = k;
  out << var;
  EXPECT_EQ("7", out.str());
  out.str(std::string());
  var = l;
  out << var;
  EXPECT_EQ("8", out.str());
  out.str(std::string());
  var = m;
  out << var;
  EXPECT_EQ("1.5", out.str());
  out.str(std::string());
  var = n;
  out << var;
  EXPECT_EQ("3.1415", out.str());
  out.str(std::string());
  var = o;
  out << var;
  EXPECT_EQ("2.7182", out.str());
  out.str(std::string());
  var = p;
  out << var;
  EXPECT_EQ("Hello World!", out.str());
  out.str(std::string());
  var = q;
  out << var;
  EXPECT_EQ("Goodbye World!", out.str());
  out.str(std::string());
}

TEST(VariableTest, StreamVectorOperator) {
  std::vector<bool> a{true, false, true};
  std::vector<char> b{'a', 'b', 'c'};
  std::vector<signed char> c{'b', 'c', 'd'};
  std::vector<unsigned char> d{'c', 'd', 'e'};
  std::vector<signed short int> e{1, 2, 3};
  std::vector<unsigned short int> f{2, 3, 4};
  std::vector<signed int> g{3, 4, 5};
  std::vector<unsigned int> h{4, 5, 6};
  std::vector<signed long int> i{5, 6, 7};
  std::vector<unsigned long int> j{6, 7, 8};
  std::vector<signed long long int> k{7, 8, 9};
  std::vector<unsigned long long int> l{8, 9, 10};
  std::vector<float> m{1.5, 1.7, 1.9};
  std::vector<double> n{1.7, 1.9, 2.1};
  std::vector<long double> o{1.9, 2.1, 2.3};
  std::vector<std::string> p{"Hello", "World!"};
  std::vector<const char*> q{"Goodbye", "World!"};
  std::stringstream out;
  estl::variable::Variable var;
  var = a;
  out << var;
  EXPECT_EQ("1, 0, 1", out.str());
  out.str(std::string());
  var = b;
  out << var;
  EXPECT_EQ("a, b, c", out.str());
  out.str(std::string());
  var = c;
  out << var;
  EXPECT_EQ("b, c, d", out.str());
  out.str(std::string());
  var = d;
  out << var;
  EXPECT_EQ("c, d, e", out.str());
  out.str(std::string());
  var = e;
  out << var;
  EXPECT_EQ("1, 2, 3", out.str());
  out.str(std::string());
  var = f;
  out << var;
  EXPECT_EQ("2, 3, 4", out.str());
  out.str(std::string());
  var = g;
  out << var;
  EXPECT_EQ("3, 4, 5", out.str());
  out.str(std::string());
  var = h;
  out << var;
  EXPECT_EQ("4, 5, 6", out.str());
  out.str(std::string());
  var = i;
  out << var;
  EXPECT_EQ("5, 6, 7", out.str());
  out.str(std::string());
  var = j;
  out << var;
  EXPECT_EQ("6, 7, 8", out.str());
  out.str(std::string());
  var = k;
  out << var;
  EXPECT_EQ("7, 8, 9", out.str());
  out.str(std::string());
  var = l;
  out << var;
  EXPECT_EQ("8, 9, 10", out.str());
  out.str(std::string());
  var = m;
  out << var;
  EXPECT_EQ("1.5, 1.7, 1.9", out.str());
  out.str(std::string());
  var = n;
  out << var;
  EXPECT_EQ("1.7, 1.9, 2.1", out.str());
  out.str(std::string());
  var = o;
  out << var;
  EXPECT_EQ("1.9, 2.1, 2.3", out.str());
  out.str(std::string());
  var = p;
  out << var;
  EXPECT_EQ("Hello, World!", out.str());
  out.str(std::string());
  var = q;
  out << var;
  EXPECT_EQ("Goodbye, World!", out.str());
  out.str(std::string());
}
