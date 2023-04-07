#pragma once
#include "ImWrapValueElement.h"

namespace ImWrap {
template <typename T> class ValueLabel : public ValueElement<T> {
public:
  // Constructor
  ValueLabel(const std::string &label = {}, const T &value = {})
      : ValueElement<T>(label, value) {}

  // Destructor
  virtual ~ValueLabel() override = default;

protected:
  // Paint Element
  virtual void paintElement() override {
    ImGui::AlignTextToFramePadding();
    ImGui::Text(ValueElement<T>::_label.c_str(), ValueElement<T>::_value);
  }
};

} // namespace ImWrap
