#pragma once
#include "ImwMultiValueElement.h"
#include <algorithm>
#include <array>

namespace Imw {
template <class T> class SpinBoxAB : public MultiValueElement<T, 2> {
public:
  // Constructot
  SpinBoxAB(const std::string &label = {}) : MultiValueElement<T, 2>(label) {}

  // Destructor
  virtual ~SpinBoxAB() override = default;

protected:
  virtual void paintElement() override { paintElementImpl(); }
  inline void paintElementImpl() {}
};

template <> inline void SpinBoxAB<int>::paintElementImpl() {
  int step{1};
  int step_fast{100};
  ImGuiInputTextFlags flags{0};
  ImGui::InputScalarN(_label.c_str(), ImGuiDataType_S32,
                      (void *)MultiValueElement<int, 2>::_value.data(),
                      MultiValueElement<int, 2>::_value.size(),
                      (void *)(step > 0 ? &step : NULL),
                      (void *)(step_fast > 0 ? &step_fast : NULL), NULL, flags);
}

} // namespace Imw
