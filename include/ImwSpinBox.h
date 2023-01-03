#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <class T> class SpinBox : public ValueElement<T> {
public:
  SpinBox(const std::string &label = {}) : ValueElement<T>(label) {}

  virtual ~SpinBox() override = default;

protected:
  virtual void paintElement() override { paintElementImpl(); }
  void paintElementImpl() {}
};

template <> inline void SpinBox<int>::paintElementImpl() {
  int value{_value};
  _changed = ImGui::InputInt(_label.c_str(), &value);
  if (_changed) {
    setValue(value);
  }
}
} // namespace Imw
