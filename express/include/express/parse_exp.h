#pragma once

#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "boost/variant.hpp"

namespace express {

enum class data_type {
  UNKOWN,
  BOOL,
  LOGICAL,
  REAL,
  NUMBER,
  STRING,
  INTEGER,
  ENTITY,
  ENUM,
  SELECT,
  ALIAS,
  BINARY
};
constexpr char const* data_type_str[] = {
    "UNKOWN",  "BOOL",   "LOGICAL", "REAL",   "NUMBER", "STRING",
    "INTEGER", "ENTITY", "ENUM",    "SELECT", "ALIAS",  "BINARY"};

struct parser_exception : public std::exception {
  parser_exception(char const* from, char const* to) : from_{from}, to_{to} {}
  char const *from_, *to_;
};

struct list;
struct schema;

struct type_name {
  std::string name_;
};

using member_type = boost::variant<type_name, boost::recursive_wrapper<list>>;

struct list {
  unsigned min_{0}, max_{std::numeric_limits<unsigned>::max()};
  member_type m_;
};

struct member {
  bool is_list(schema const&) const;
  std::string const& get_type_name() const;

  std::string name_;
  member_type type_;
  bool optional_;
};

struct type {
  std::string name_;
  data_type data_type_{data_type::UNKOWN};
  std::vector<std::string> details_;
  std::string subtype_of_;
  std::vector<member> members_;
  bool list_{false};
  unsigned min_size_{0}, max_size_{std::numeric_limits<unsigned>::max()};
  std::string alias_;
};

struct schema {
  std::string name_;
  std::vector<type> types_;
  std::unordered_map<std::string, type const*> type_map_;
};

schema parse(std::string_view);

bool is_list(schema const&, std::string const& type_name);

}  // namespace express
