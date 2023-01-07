#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <class T> class Slider : public ValueElement<T> {
public:
  Slider(const std::string &label = {}) : ValueElement<T>(label) {
    ValueElement<T>::setValueLimits({T(0), T(9)});
  }

  virtual ~Slider() override = default;

protected:
  virtual void paintElement() override { paintElementImpl(); }
  void paintElementImpl() {}
};

template <> inline void Slider<int>::paintElementImpl() {
  _changed = ImGui::SliderInt(_label.c_str(), &_value, _valueLimits.first,
                              _valueLimits.second);
}

template <> inline void Slider<float>::paintElementImpl() {
  _changed = ImGui::SliderFloat(_label.c_str(), &_value, _valueLimits.first,
                                _valueLimits.second);
}

} // namespace Imw
