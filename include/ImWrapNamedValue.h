#pragma once
#include <string>
#include <vector>

namespace ImWrap {
template <typename T> class NamedValue {
public:
  NamedValue() = default;

  NamedValue(const std::string &name, const T &value = {})
      : _name{name}
      , _value{value} {}

  NamedValue(const T &value, const std::string &name)
      : _value{value}, _name{name} {}

  NamedValue(const std::pair<const T &, const std::string> pair)
      : _value(pair.first), _name(pair.second) {}

  ~NamedValue() = default;

  // Set Value
  inline void setValue(const T &value) { _value = value; }

  // Get Value
  inline const T &value() const { return _value; }
  const T &operator()() const { return _value; }
  T *valuePtr() { return &_value; }

  // Set Name
  inline void setName(const std::string &name) { _name = name; }

  // Get Name
  inline const std::string &name() const { return _name; }
  inline const char *namePtr() const { return _name.c_str(); }

  // Compare
  inline bool operator<(const NamedValue &value) const {
    return _value < value._value;
  }

  inline bool operator==(const NamedValue &value) const {
    return _value == value._value;
  }

  // Convert
  operator const T &() const { return _value; }

private:
  T _value{};
  std::string _name;
};

} // namespace ImWrap
