#pragma once
#include "ImwValueElement.h"

namespace Imw {
template <class T> class ValueLabel : public ValueElement<T> {
public:
  ValueLabel(const std::string &label = {}) : ValueElement<T>(label) {}
  virtual ~ValueLabel() override = default;

protected:
  virtual void paintElement() override {
    ImGui::AlignTextToFramePadding();
    ImGui::Text(ValueElement<T>::_label.c_str(), ValueElement<T>::_value);
  }
};

} // namespace Imw
