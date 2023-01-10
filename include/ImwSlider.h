#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <class T> class Slider : public ValueElement<T> {
public:
  Slider(const std::string &label = {}) : ValueElement<T>(label) {
    ValueElement<T>::setValueLimits({T(0), T(9)});
  }

  virtual ~Slider() override = default;

  // Text format
  void setTextFormat(const std::string &format) { _format = format; }
  const std::string &textFormat() const { return _format; }

protected:
  virtual void paintElement() override { paintElementImpl(); }
  void paintElementImpl() {}

  std::string _format{};
};

template <> inline void Slider<int>::paintElementImpl() {
  const char *format{_format.empty() ? nullptr : _format.c_str()};
  _changed = ImGui::SliderInt(_label.c_str(), &_value, _valueLimits.first,
                              _valueLimits.second, format);
}

template <> inline void Slider<float>::paintElementImpl() {
  const char *format{_format.empty() ? nullptr : _format.c_str()};
  _changed = ImGui::SliderFloat(_label.c_str(), &_value, _valueLimits.first,
                                _valueLimits.second, format);
}

} // namespace Imw
