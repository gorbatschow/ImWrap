#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <typename T> class Slider : public ValueElement<T> {
  using Base = ValueElement<T>;

public:
  // Constructor
  Slider(const std::string &label = {}) : Base(label) { SliderImpl(); }

  // Destructor
  virtual ~Slider() override = default;

  // Set Value
  virtual void setValue(const T &value, std::size_t index = 0) override {
    Base::setValue(std::clamp(value, _valueLimits.first, _valueLimits.second));
  }

  // Set Value Limits
  virtual void setValueLimits(const std::pair<T, T> &limits,
                              std::size_t index = 0) override {
    _valueLimits = limits;
    Base::setValue(std::clamp(Base::currentValue(), _valueLimits.first,
                              _valueLimits.second));
  }

protected:
  // Paint Element
  virtual void paintElement() override { paintElementImpl(); }
  void paintElementImpl() {}
  void SliderImpl() {}

  std::pair<T, T> _valueLimits{T(0), T(100)};
};

// Slider<int>
// -----------------------------------------------------------------------------
template <> inline void Slider<int>::SliderImpl() {}

template <> inline void Slider<int>::paintElementImpl() {
  const char *format{_textFormat.empty() ? nullptr : _textFormat.c_str()};
  _changed = ImGui::SliderInt(_label.c_str(), &_value, _valueLimits.first,
                              _valueLimits.second, format);
}

// Slider<float>
// -----------------------------------------------------------------------------
template <> inline void Slider<float>::SliderImpl() {}

template <> inline void Slider<float>::paintElementImpl() {
  const char *format{_textFormat.empty() ? nullptr : _textFormat.c_str()};
  _changed = ImGui::SliderFloat(_label.c_str(), &_value, _valueLimits.first,
                                _valueLimits.second, format);
}

} // namespace Imw
