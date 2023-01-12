#pragma once
#include "ImwMultiValueElement.h"
#include <algorithm>
#include <array>

namespace Imw {
template <typename T> class MultiSpinBox : public MultiValueElement<T> {
public:
  // Constructot
  MultiSpinBox(std::size_t count, const std::string &label = {})
      : MultiValueElement<T>(count, label) {}

  // Destructor
  virtual ~MultiSpinBox() override = default;

protected:
  virtual void paintElement() override { paintElementImpl(); }
  inline void paintElementImpl() {}
};

template <> inline void MultiSpinBox<int>::paintElementImpl() {
  int step{1};
  int step_fast{100};
  ImGuiInputTextFlags flags{0};
  ImGui::InputScalarN(_label.c_str(), ImGuiDataType_S32,
                      (void *)MultiValueElement<int>::_valueList.data(),
                      MultiValueElement<int>::_valueList.size(),
                      (void *)(step > 0 ? &step : NULL),
                      (void *)(step_fast > 0 ? &step_fast : NULL), NULL, flags);
}
} // namespace Imw
