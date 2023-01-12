#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <typename T> class Slider : public ValueElement<T> {
public:
  // Constructor
  Slider(const std::string &label = {}) : ValueElement<T>(label) {
    ValueElement<T>::setValueLimits({T(0), T(9)});
  }

  // Destructor
  virtual ~Slider() override = default;

protected:
  // Paint Element
  virtual void paintElement() override { paintElementImpl(); }
  void paintElementImpl() {}
};

template <> inline void Slider<int>::paintElementImpl() {
  const char *format{_textFormat.empty() ? nullptr : _textFormat.c_str()};
  _changed = ImGui::SliderInt(_label.c_str(), &_value, _valueLimits.first,
                              _valueLimits.second, format);
}

template <> inline void Slider<float>::paintElementImpl() {
  const char *format{_textFormat.empty() ? nullptr : _textFormat.c_str()};
  _changed = ImGui::SliderFloat(_label.c_str(), &_value, _valueLimits.first,
                                _valueLimits.second, format);
}

} // namespace Imw
