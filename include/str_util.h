//
// Created by jintian on 7/14/17.
//

#ifndef _T_STRING_H
#define _T_STRING_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cmath>
#include <vector>
#include <sstream>

#include "google/protobuf/stubs/strutil.h"


using namespace std;

namespace thor {
namespace str_util {

using google::protobuf::Join;
using google::protobuf::StrAppend;
using google::protobuf::StrCat;
using google::protobuf::StringPiece;


void SplitString(const std::string& s, std::vector<std::string>& v,
                 const std::string& c);
string join_str(const std::string& c, vector<string> s_v);

void StripString(vector<string> s_v, const string& c);

bool Replace(std::string& str, const std::string& from, const std::string& to);
void ReplaceAll(std::string& str, const std::string& from,
                const std::string& to);

// !--------------- new apis of str utils
inline bool EndWith(const std::string& ori, const std::string& pat) {
  return StringPiece(ori).ends_with(pat);
}
inline bool StartWith(const std::string& ori, const std::string& pat) {
  return StringPiece(ori).starts_with(pat);
}
int split(const std::string& str, char ch, std::vector<std::string>* result);
void ltrim(std::string* str);
inline std::string ltrim(std::string str) {
  ltrim(&str);
  return str;
}
void rtrim(std::string* str);
inline std::string rtrim(std::string str) {
  rtrim(&str);
  return str;
}
void trim(std::string* str);
inline std::string trim(std::string str) {
  trim(&str);
  return str;
}

template <typename T>
std::string Print(const T& val) {
  std::ostringstream oss;
  oss << val;
  return oss.str();
}

/**
 * @brief Make arrays, conatiners and iterators printable.
 *
 * Usage:
 *   vector<int> vec = {1, 2, 3};
 *   std::cout << PrintIter(vec);
 *   std::cout << PrintIter(vec, ",");
 *   std::cout << PrintIter(vec.begin(), vec.end());
 *   std::cout << PrintIter(vec.begin(), vec.end(), "|");
 *
 *   int array[] = {1, 2, 3};
 *   std::cout << PrintIter(array);
 *   std::cout << PrintIter(array, "|");
 *   std::cout << PrintIter(array + 0, array + 10, "|");
 */
template <typename Iter>
std::string PrintIter(const Iter& begin, const Iter& end,
                      const std::string& delimiter = " ") {
  std::string result;
  Join(begin, end, delimiter.c_str(), &result);
  return result;
}

template <typename Iter>
std::string PrintIter(const Iter& begin, const Iter& end,
                      const std::function<std::string(Iter)> transformer,
                      const std::string& delimiter = " ") {
  std::string result;
  if (transformer) {
    for (auto iter = begin; iter != end; ++iter) {
      if (iter == begin) {
        StrAppend(&result, transformer(*iter));
      } else {
        StrAppend(&result, delimiter, transformer(*iter));
      }
    }
  } else {
    PrintIter(begin, end, delimiter);
  }
  return result;
}

template <typename Container, typename Iter>
std::string PrintIter(const Container& container,
                      const std::function<std::string(Iter)> transformer,
                      const std::string& delimiter = " ") {
  return PrintIter(container.begin(), container.end(), transformer, delimiter);
}

template <typename Container>
std::string PrintIter(const Container& container,
                      const std::string& delimiter = " ") {
  return PrintIter(container.begin(), container.end(), delimiter);
}

template <typename T, int length>
std::string PrintIter(T (&array)[length], T* end,
                      const std::string& delimiter = " ") {
  std::string result;
  Join(array, end, delimiter.c_str(), &result);
  return result;
}

template <typename T, int length>
std::string PrintIter(T (&array)[length], const std::string& delimiter = " ") {
  return PrintIter(array, array + length, delimiter);
}

/**
 * @brief Make conatiners and iterators printable. Similar to PrintIter but
 *        output the DebugString().
 */
template <typename Iter>
std::string PrintDebugStringIter(const Iter& begin, const Iter& end,
                                 const std::string& delimiter = " ") {
  std::string result;
  for (auto iter = begin; iter != end; ++iter) {
    if (iter == begin) {
      StrAppend(&result, iter->DebugString());
    } else {
      StrAppend(&result, delimiter, iter->DebugString());
    }
  }
  return result;
}

template <typename Container>
std::string PrintDebugStringIter(const Container& container,
                                 const std::string& delimiter = " ") {
  return PrintDebugStringIter(container.begin(), container.end(), delimiter);
}

// !-------- Not implemented yet
std::string DecodeBase64(const std::string& base64_str);
std::string EncodeBase64(const std::string& in);

}  // namespace str_util
}  // namespace thor

#endif  //_T_STRING_H
