#pragma once
#include "ImwMultiValueElement.h"
#include <algorithm>
#include <array>

namespace Imw {
template <class T, std::size_t N>
class MultiSpinBox : public MultiValueElement<T, N> {
public:
  // Constructot
  MultiSpinBox(const std::string &label = {})
      : MultiValueElement<T, N>(label) {}

  // Destructor
  virtual ~MultiSpinBox() override = default;

protected:
  virtual void paintElement() override { paintElementImpl(); }
  inline void paintElementImpl() {}
};

template <> inline void MultiSpinBox<>::paintElementImpl() {
  int step{1};
  int step_fast{100};
  ImGuiInputTextFlags flags{0};
  ImGui::InputScalarN(_label.c_str(), ImGuiDataType_S32,
                      (void *)MultiValueElement<int, N>::_value.data(),
                      MultiValueElement<int, N>::_value.size(),
                      (void *)(step > 0 ? &step : NULL),
                      (void *)(step_fast > 0 ? &step_fast : NULL), NULL, flags);
}

} // namespace Imw
